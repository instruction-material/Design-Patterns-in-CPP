"""Verify the downloadable roles and independent ownership boundary cases."""
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]

DEMOS = {
    3: (["Preview: Sketch", "Claimed: (empty)", "Inbox: occupied"],
        ["Preview: Sketch", "Claimed: Sketch", "Inbox: empty"]),
    4: (["(unrendered)"] * 3, ["Show: Welcome", "Pause: 3 seconds", "Show: Map"]),
    5: (["Missing"] * 3, ["Ready", "Below", "Missing"]),
    6: (["2", "2 true", "0"], ["2", "1 false", "0"])
}

REFERENCE_CASES = {
    3: """
    Inbox first(std::make_unique<Draft>(Draft{"Original"}));
    const Draft* seen = first.preview();
    auto owner = first.take();
    assert(owner.get() == seen);
    assert(first.preview() == nullptr && first.take() == nullptr);
    owner->title = "Edited";
    Inbox again(std::move(owner));
    assert(!owner && again.preview()->title == "Edited");
""",
    4: """
    TourStep original = Card{"First"};
    TourStep copy = original;
    std::get<Card>(original).label = "Second";
    assert(render(copy) == "Show: First");
    assert(render(original) == "Show: Second");
    assert(render(Pause{0}) == "Pause: 0 seconds");
    assert(render(Card{""}) == "Show: ");
""",
    5: """
    struct CountingProbe final : Probe {
        mutable int calls = 0;
        std::optional<int> read() const override { ++calls; return 0; }
    } counted;
    const OfflineProbe offline;
    assert(inspect(counted, 1) == Status::Below && counted.calls == 1);
    assert(inspect(counted, 0) == Status::Ready && counted.calls == 2);
    assert(inspect(offline, 0) == Status::Missing);
    assert(inspect(FixedProbe(-3), -3) == Status::Ready);
""",
    6: """
    static_assert(!std::is_copy_constructible_v<Lease>);
    static_assert(!std::is_copy_assignable_v<Lease>);
    static_assert(std::is_nothrow_move_assignable_v<Lease>);
    Registry first, second;
    {
        Lease held(first), spare(second);
        Lease moved(std::move(held));
        assert(first.active() == 1 && second.active() == 1 && !held.ownsSlot());
        Lease& alias = moved;
        moved = std::move(alias);
        assert(moved.ownsSlot() && first.active() == 1);
        moved = std::move(held);
        assert(!moved.ownsSlot() && first.active() == 0);
        moved = std::move(spare);
        assert(moved.ownsSlot() && !spare.ownsSlot() && second.active() == 1);
    }
    assert(first.active() == 0 && second.active() == 0);
"""
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
            folder, = ROOT.glob(f'DPC-{n:02d}-dpc?-*supplemental-*')
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
