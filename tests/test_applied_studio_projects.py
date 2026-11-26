"""Verify both practice roles and independent applied studio projects and extensions."""
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
DEMOS = {
    1: (['Original address: false', 'Returned: (empty)', 'Lute removed: true', 'Unknown is empty: true', 'Drum remains: false'], ['Original address: true', 'Returned: lute', 'Lute removed: true', 'Unknown is empty: true', 'Drum remains: true']),
    2: (['(no sign)', '(no sign)', '(no sign)', '(no sign)'], ['Maps', 'Maps (room 4)', 'Maps (room 4)', 'Maps']),
    3: (['true false false', 'false false false', 'Ada:2'], ['true true false', 'true false true', 'Mina:3', 'Jo:2']),
    4: (['ready=5', 'repair=1', 'ready=0', 'repair=0', 'retired=0'], ['ready=5', 'repair=1', 'ready=5', 'repair=1', 'retired=3']),
}

REFERENCE_CASES = {
    1: """
    Bench bench;
    assert(!bench.accept(nullptr));
    auto first = std::make_unique<Instrument>(Instrument{"lute"});
    const auto* before = first.get();
    assert(bench.accept(std::move(first)) && !first);
    assert(bench.accept(std::make_unique<Instrument>(Instrument{"drum"})));
    assert(bench.accept(std::make_unique<Instrument>(Instrument{"lute"})));
    assert(bench.find("lute") == before);
    auto returned = bench.extract("lute");
    assert(returned.get() == before && bench.find("lute") != before);
    assert(bench.extract("lute") && !bench.extract("lute") && bench.find("drum"));
""",
    2: """
    struct Trace final : Style {
        mutable int calls = 0;
        std::string format(const Exhibit& exhibit) const override {
            ++calls;
            return std::to_string(exhibit.room) + ":" + exhibit.title;
        }
    } trace;
    const Brief brief;
    const Detailed detailed;
    SignPrinter printer(brief);
    const Exhibit printmaking{"Printmaking", 8};
    assert(printer.text(printmaking) == "Printmaking");
    printer.use(detailed);
    assert(printer.text(printmaking) == "Printmaking (room 8)");
    printer.use(trace);
    assert(printer.text({"Glass", 12}) == "12:Glass" && trace.calls == 1);
    printer.use(brief);
    assert(printer.text(printmaking) == "Printmaking" && trace.calls == 1);
""",
    3: """
    Workshop workshop;
    assert(workshop.admit(DeskSlip{"A", 1}));
    for (const auto invalid : {"", "1", "0", "13", "3x", " 4", "9999999999999"}) {
        assert(!workshop.admit(MailSlip{"X", invalid}));
    }
    assert(!workshop.admit(MailSlip{"", "12"}));
    assert(workshop.admit(MailSlip{"B", "12"}));
    assert(!workshop.admit(DeskSlip{"C", 12}));
    assert(workshop.withdraw(1) && !workshop.withdraw(1));
    assert(workshop.admit(MailSlip{"D", "1"}));
    assert(workshop.guests().size() == 2 && workshop.guests().front().label == "B");
    assert(workshop.guests().back().label == "D");
""",
    4: """
    const auto none = summarize({});
    assert(none.ready == 0 && none.repair == 0 && none.retired == 0);
    const auto full = summarize({{State::Repair, 2}, {State::Ready, 3},
        {State::Repair, 5}, {State::Retired, 42}, {State::Retired, -4}, {State::Ready, 0}});
    assert(full.ready == 3 && full.repair == 7 && full.retired == 42);
    const auto separate = summarize({{State::Retired, 1}});
    assert(separate.ready == 0 && separate.repair == 0 && separate.retired == 1);
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
            folder, = ROOT.glob(f'DPC-{n:02d}-pattern-implementation-lab-*')
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
