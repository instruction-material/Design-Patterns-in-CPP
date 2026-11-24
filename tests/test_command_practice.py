"""Run both downloadable roles and exercise scanner and history boundaries."""
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SCAN = ROOT / "DPC-15-dpc7-command-and-state-supplemental-2"
UNDO = ROOT / "DPC-16-dpc7-command-and-state-supplemental-3"

def run(source, build_dir, data=""):
    binary = build_dir / "editor"
    subprocess.run([os.environ.get("CXX", "c++"), "-std=c++20", "-Wall", "-Wextra",
                    "-Werror", "-pedantic", "-fsanitize=address,undefined",
                    "-fno-sanitize-recover=all", str(source), "-o", str(binary)], check=True)
    return subprocess.run([str(binary)], input=data, capture_output=True,
                          text=True, check=True).stdout.splitlines()

def snapshot(mode, text):
    return f"Mode={mode} document={text}"

def main():
    with tempfile.TemporaryDirectory() as temp:
        build = Path(temp)
        starter = SCAN / "starter/main.cpp"
        reference = SCAN / "solution/main.cpp"
        assert run(starter, build, 'mode review\nappend "A"\nundo\n') == [
            snapshot("review", ""), "Syntax error", snapshot("review", "")]
        lines = ['undo', 'append "first draft"', 'mode review', 'replace "blocked"',
                 'replace missing', 'append "incomplete', 'append "!" extra', 'mode other',
                 'undo extra', 'delete "x"', 'append "!"', 'undo', 'mode draft',
                 r'replace "say \"hi\""', 'replace ""', 'undo']
        output = run(reference, build, "\n".join(lines) + "\n")
        assert output == [snapshot("draft", ""), snapshot("draft", "first draft"),
                          snapshot("review", "first draft"), "Mode review rejected replace",
                          snapshot("review", "first draft"), *(["Syntax error"] * 6),
                          snapshot("review", "first draft!"), snapshot("review", "first draft"),
                          snapshot("draft", "first draft"), snapshot("draft", 'say "hi"'),
                          snapshot("draft", ""), snapshot("draft", 'say "hi"')], output

        for role, restored in [("starter", "A"), ("solution", "AB")]:
            output = run(UNDO / role / "main.cpp", build)
            assert output == [snapshot("draft", "A"), snapshot("draft", restored),
                              "Mode review rejected replace", snapshot("review", restored if role == "solution" else ""),
                              snapshot("review", "AC" if role == "solution" else "C")], output

        # Run a second independent transcript against the reference types.
        external = build / "nested.cpp"
        model = (UNDO / "solution/main.cpp").read_text().split("int main() {")[0]
        external.write_text(model + """
int main() {
    EditorSession s;
    s.enqueue(std::make_unique<AppendCommand>("first"));
    s.enqueue(std::make_unique<ReplaceCommand>("second"));
    s.runQueue();
    s.undoLast(); s.undoLast(); s.undoLast(); s.print();
    s.redoLast(); s.print();
    s.setMode(std::make_unique<ReviewMode>());
    s.redoLast(); s.print();
    s.setMode(std::make_unique<DraftMode>());
    s.redoLast(); s.redoLast(); s.print();
    s.undoLast(); s.print();
}
""")
        assert run(external, build) == [snapshot("draft", ""), snapshot("draft", "first"),
                                        snapshot("review", "first"), snapshot("draft", "second"),
                                        snapshot("draft", "first")]

if __name__ == "__main__":
    main()
