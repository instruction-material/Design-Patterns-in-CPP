"""Verify both practice roles and independent final applied studio cases."""
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
DEMOS = {
    27: (['(returned)', '1', '(returned)'], ['tripod', '1', '(returned)']),
    28: (['-1 true', '0'], ['7 true', '1']),
    29: (['Kim Ada Bo ', 'Kim Ada Bo ', 'Kim Ada Bo '], ['Ada Bo Kim ', 'Kim Bo Ada ', 'Kim Ada Bo ']),
    30: (['0', '0', '0'], ['3', '8', '9']),
    31: (['Shelf: 25.40 cm', 'Door: 10.00 cm'], ['Shelf: 25.40 cm', 'Door: 25.40 cm']),
    32: (['Gallery', 'Gallery', '(missing)', '(missing)', 'Calls: 4', 'Calls: 5'], ['Gallery', 'Gallery', '(missing)', '(missing)', 'Calls: 2', 'Calls: 3']),
    33: (['10'], ['10']),
    34: (['draft', 'map'], ['draft', 'map', 'review']),
}

REFERENCE_CASES = {
    27: """
    auto own = std::make_shared<Checkout>(Checkout{"marker"});
    const Display first(own), second(own), empty({});
    assert(first.show() == "marker" && own.use_count() == 1);
    own->label = "brush";
    assert(second.show() == "brush" && own.use_count() == 1);
    own.reset();
    assert(first.show() == "(returned)" && second.show() == "(returned)");
    assert(empty.show() == "(returned)");
""",
    28: """
    int releases = 0;
    {
        auto empty = open(0, releases);
        assert(!empty && releases == 0);
        auto first = open(2, releases);
        auto second = open(1, releases);
        assert(first[0] == 0 && first[1] == 0 && second[0] == 0);
        first[1] = 9;
        auto moved = std::move(first);
        assert(!first && moved[1] == 9 && releases == 0);
        moved.reset();
        assert(releases == 1);
    }
    assert(releases == 2);
""",
    29: """
    const std::vector<Job> jobs{{"z", 2},{"c", 1},{"a", 2},{"b", 1}};
    const auto priorities = ordered(jobs, [](const Job& a, const Job& b) { return a.priority > b.priority; });
    assert(priorities[0].title == "z" && priorities[1].title == "a");
    assert(priorities[2].title == "c" && priorities[3].title == "b");
    const auto titles = ordered(jobs, [](const Job& a, const Job& b) { return a.title < b.title; });
    assert(titles.front().title == "a" && titles.back().title == "z");
    assert(jobs[0].title == "z" && jobs[1].title == "c");
""",
    30: """
    int calls = 0;
    Session session([&calls](int value) { ++calls; return value; });
    assert(session.measure(5) == 5 && calls == 1);
    int offset = -3;
    session.use([offset](int value) { return value + offset; });
    offset = 100;
    assert(session.measure(5) == 7 && calls == 1);
    assert(session.measure(0) == 4);
    session.use([](int value) { return value; });
    assert(session.measure(4) == 8);
""",
    31: """
    const auto half = normalize({"Frame", 0.5});
    assert(half.label == "Frame" && half.centimetres > 1.26999 && half.centimetres < 1.27001);
    assert(normalize({"Guide", 0.0}).centimetres == 0.0);
    const auto longCut = normalize({"Runner", 100.0});
    assert(longCut.centimetres > 253.999 && longCut.centimetres < 254.001);
""",
    32: """
    Catalogue source{{{1, ""}}};
    Memo memo(source);
    const auto empty = memo.find(1);
    assert(empty && empty->empty());
    assert(memo.find(1).has_value() && !memo.find(2));
    source.titles.emplace(2, "Poster");
    assert(!memo.find(2) && source.calls == 2);
    memo.clear();
    assert(memo.find(2) == "Poster" && source.calls == 3);
""",
    33: """
    const std::vector<int> times{3, 6, 16, 19};
    assert((longGaps(times, 2) == std::vector<std::int64_t>{3,10,3}));
    assert(longGaps(times, 10).empty());
    assert(longGaps({0,0,1}, 0) == std::vector<std::int64_t>{1});
    assert(longGaps({}, 0).empty() && longGaps({20}, 0).empty());
    assert((times == std::vector<int>{3,6,16,19}));
""",
    34: """
    const Revision left{{"a","b"}}, right{{"b","c"}};
    const auto merged = combined(left, right);
    assert((merged.topics == std::set<std::string>{"a","b","c"}));
    assert(combined(right, left).topics == merged.topics);
    assert(combined({}, left).topics == left.topics);
    assert(combined(left, {}).topics == left.topics);
    assert(combined(merged, merged).topics == merged.topics);
    assert((left.topics == std::set<std::string>{"a","b"}));
    assert((right.topics == std::set<std::string>{"b","c"}));
""",
}

def build(source, executable):
    subprocess.run([os.environ.get('CXX', 'c++'), '-std=c++20', '-Wall', '-Wextra',
                    '-Werror', '-pedantic', '-fsanitize=address,undefined',
                    '-fno-sanitize-recover=all', str(source), '-o', str(executable)], check=True)

def main():
    with tempfile.TemporaryDirectory() as temp:
        work = Path(temp)
        binary = work / 'exercise'
        harness = work / 'test.cpp'
        for n, outputs in DEMOS.items():
            folder, = ROOT.glob(f'DPC-{n:02d}-applied-studio-*-supplemental-*')
            for role, expected in zip(('starter', 'solution'), outputs, strict=True):
                source = folder / role / 'main.cpp'
                build(source, binary)
                assert subprocess.check_output([binary], text=True).splitlines() == expected
            ref = (folder / 'solution/main.cpp').read_text().split('int main() {')[0]
            harness.write_text('#include <cassert>\n#include <type_traits>\n' + ref +
                               'int main() {' + REFERENCE_CASES[n] + '}\n')
            build(harness, binary)
            subprocess.run([binary], check=True)
            print(f'Verified {folder.name}: both roles and independent checks', flush=True)

if __name__ == '__main__':
    main()
