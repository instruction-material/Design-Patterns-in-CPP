"""Check both delivered roles and new traversal cases without changing their files."""
from pathlib import Path
import os
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
CASES = {
    17: """
    Playlist root;
    auto nested = std::make_unique<Playlist>();
    auto inner = std::make_unique<Playlist>();
    inner->add(std::make_unique<Track>("Repeated", 17));
    nested->add(std::make_unique<Track>("Repeated", 31));
    nested->add(std::move(inner));
    root.add(std::make_unique<Playlist>());
    root.add(std::move(nested));
    assert(root.totalSeconds() == 48);
    assert(Playlist{}.totalSeconds() == 0);
""",
    18: """
    const Node root{"root", {{"left", {{"leaf", {}}}}, {"right", {}}}};
    OutlineCursor first(root), second(root);
    assert(first.next() == &root);
    assert(first.next() == &root.children[0]);
    assert(second.next() == &root);
    assert(first.next() == &root.children[1]);
    assert(first.next() == &root.children[0].children[0]);
    assert(first.next() == nullptr && first.next() == nullptr);
    const Node single{"single", {}};
    OutlineCursor exhausted(single);
    assert(exhausted.next() == &single && exhausted.next() == nullptr);
"""
}

def build(source, binary):
    subprocess.run([os.environ.get("CXX", "c++"), "-std=c++20", "-Wall", "-Wextra",
                    "-Werror", "-pedantic", "-fsanitize=address,undefined",
                    "-fno-sanitize-recover=all", str(source), "-o", str(binary)], check=True)

def main():
    expected = {
        17: {"starter": ["0"], "solution": ["255"]},
        18: {"starter": ["Course"], "solution": ["Course", "Week 1", "Week 2", "Arrays", "Loops", "Grid"]}
    }
    with tempfile.TemporaryDirectory() as directory:
        work = Path(directory)
        binary = work / "exercise"
        for number, roles in expected.items():
            folder, = ROOT.glob(f"DPC-{number}-dpc8-*")
            for role, lines in roles.items():
                source = folder / role / "main.cpp"
                build(source, binary)
                assert subprocess.check_output([binary], text=True).splitlines() == lines
            code = (folder / "solution/main.cpp").read_text().split("int main() {")[0]
            test = work / "exercise.cpp"
            test.write_text("#include <cassert>\n" + code + "int main() {" + CASES[number] + "}\n")
            build(test, binary)
            subprocess.run([binary], check=True)
            print(f"Verified {folder.name}: starter, reference and independent cases", flush=True)

if __name__ == "__main__":
    main()
