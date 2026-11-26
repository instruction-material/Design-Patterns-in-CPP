"""Verify both practice roles and independent refactoring and capstone cases."""
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
DEMOS = {
    23: (['150 200', '150 200'], ['150 200', '50 50']),
    24: (['Morning drawing: 2'], ['Morning drawing: 2']),
    25: (['Minutes: 0'], ['Sketch', 'Assemble', 'Minutes: 35']),
    26: (['false', 'A', 'B', 'C', 'D'], ['false', 'B', 'D', 'A', 'C']),
}

REFERENCE_CASES = {
    23: """
    const Fees defaults;
    const Fees custom{0, 900};
    assert(feeFor(Loan::Ordinary, 2, defaults) == 150);
    assert(feeFor(Loan::Oversize, 2, defaults) == 400);
    assert(feeFor(Loan::Ordinary, 10, custom) == 0);
    assert(feeFor(Loan::Oversize, 3, custom) == 2700);
    assert(feeFor(Loan::Oversize, 0, custom) == 0);
    assert(feeFor(Loan::Oversize, -7, custom) == 0);
    assert(feeFor(Loan::Oversize, 4000000, custom) == 3600000000LL);
""",
    24: """
    Booking booking{"Morning drawing", 2};
    static_assert(std::is_same_v<decltype(preview(booking)), Receipt>);
    const auto first = preview(booking);
    booking.title = "Printmaking";
    booking.seats = 8;
    const auto second = preview(booking);
    assert(first.title == "Morning drawing" && first.seats == 2);
    assert(second.title == "Printmaking" && second.seats == 8);
    const auto temporary = preview(Booking{"Short course", 0});
    assert(temporary.title == "Short course" && temporary.seats == 0);
""",
    25: """
    const std::vector<Task> tasks{{"Sketch",15},{"Broken",-1},{"Assemble",20},{"Pack",10}};
    const auto full = buildPlan(tasks, 35);
    assert((full.titles == std::vector<std::string>{"Sketch", "Assemble"}) && full.spent == 35);
    const auto partial = buildPlan(tasks, 19);
    assert((partial.titles == std::vector<std::string>{"Sketch"}) && partial.spent == 15);
    assert(buildPlan(tasks, 10).titles.empty());
    assert(buildPlan(tasks, -1).spent == 0);
    assert(buildPlan({}, 12).spent == 0);
""",
    26: """
    Desk desk;
    assert(desk.submit({"x", true}));
    assert(desk.submit({"y", true}));
    assert(desk.submit({"a", false}));
    assert(desk.submit({"b", false}));
    assert(!desk.submit({"a", true}));
    assert(!desk.submit({"y", false}));
    assert(desk.submit({"z", true}));
    assert(desk.queue().size() == 5);
    std::string order;
    for (const auto& row : desk.queue()) order += row.id;
    assert(order == "xyzab" && !desk.queue()[3].urgent);
    Desk ordinary;
    assert(ordinary.submit({"b", false}) && ordinary.submit({"a", false}));
    assert(ordinary.queue().front().id == "b");
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
            folder, = ROOT.glob(f'DPC-{n:02d}-dpc*-*supplemental-*')
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
