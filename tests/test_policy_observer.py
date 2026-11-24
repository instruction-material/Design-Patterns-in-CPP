"""Exercise every downloadable role, alternate inputs, and the interval policy contract."""
from pathlib import Path
import os
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
CXX = os.environ.get("CXX", "c++")
FLAGS = ["-std=c++20", "-Wall", "-Wextra", "-Werror", "-pedantic",
         "-fsanitize=address,undefined", "-fno-sanitize-recover=all"]

def build(source, out):
    subprocess.run([CXX, *FLAGS, str(source), "-o", str(out)], check=True)

def output(exe, *args):
    return subprocess.check_output([str(exe), *args], text=True).splitlines()

def main():
    with tempfile.TemporaryDirectory() as temp:
        work = Path(temp)
        for n in range(9, 13):
            folder, = ROOT.glob(f"DPC-{n:02d}-*supplemental-*")
            for role in ["starter", "solution"]:
                solved = role == "solution"
                src = folder / role / "main.cpp"
                exe = work / "practice"
                build(src, exe)
                lines = output(exe)
                if n == 9:
                    assert lines == ["poster", "card", "label", "map"]
                    assert output(exe, "shortest") == (["card", "label", "map", "poster"] if solved else lines)
                    checks = """
    ShortestJob rule;
    assert(schedule({}, rule).empty());
    assert(schedule({{"single", 2}}, rule).front() == "single");
    const Jobs pending{{"slow", 5}, {"first", 1}, {"next", 1}};
    assert(schedule(pending, rule).front() == EXPECTED);
    assert(pending.front().name == "slow");
""".replace("EXPECTED", '"first"' if solved else '"slow"')
                elif n == 10:
                    assert lines == ["hot: 30 31", "outside: 9 31" if solved else "outside:"]
                    checks = """
    using Rule = OutsideBand<0, 0>;
    assert(flagged<Rule>({}).empty());
    assert(flagged<Rule>({0}).empty());
    assert(flagged<Rule>({-1, 0, 1}).size() == EXPECTED);
""".replace("EXPECTED", "2" if solved else "0")
                elif n == 11:
                    expected = ["scoreboard: blue scores", "log: blue scores", "referee: holding",
                                "log: holding", "log: offside"]
                    if not solved:
                        expected = ["scoreboard: blue scores", "referee: blue scores", "log: blue scores",
                                    "scoreboard: holding", "referee: holding", "log: holding",
                                    "scoreboard: offside", "log: offside"]
                    assert lines == expected
                    checks = """
    struct Counter : Listener {
        int count = 0;
        void receive(const Event&) override { ++count; }
    };
    MatchFeed feed;
    auto all = std::make_shared<Counter>();
    auto goals = std::make_shared<Counter>();
    feed.subscribe("", all); feed.subscribe("goal", goals);
    feed.publish({"weather", "rain"});
    assert(all->count == 1 && goals->count == EXPECTED);
    goals.reset();
    feed.publish({"goal", "tie"});
    assert(all->count == 2);
""".replace("EXPECTED", "0" if solved else "1")
                else:
                    assert lines == (["first=1 second=2 slots=0"] if solved else ["first=3 second=2 slots=2"])
                    checks = """
    static_assert(!std::is_copy_constructible_v<Connection>);
    Clock clock;
    int ticks = 0;
    auto handle = clock.subscribe([&] { ++ticks; });
    auto owner = std::move(handle);
    handle.disconnect(); clock.tick();
    assert(ticks == 1);
    owner.disconnect(); owner.disconnect(); clock.tick();
    assert(ticks == EXPECTED);
""".replace("EXPECTED", "1" if solved else "2")
                harness = work / "scenario.cpp"
                body = src.read_text().split("int main(")[0]
                harness.write_text("#include <cassert>\n#include <type_traits>\n" + body + "int main() {\n" + checks + "}\n")
                build(harness, exe)
                subprocess.run([str(exe)], check=True)
                if n == 10 and solved:
                    harness.write_text(body + "static_assert(OutsideBand<20, 10>::flags(15));\n")
                    result = subprocess.run([CXX, "-std=c++20", "-fsyntax-only", str(harness)], text=True, capture_output=True)
                    assert result.returncode and "lower limit must not exceed" in result.stderr
                print("Verified", folder.name, role, flush=True)

if __name__ == "__main__":
    main()
