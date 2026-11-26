"""Verify both practice roles and independent structural boundary cases."""
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
DEMOS = {
    13: (['accepted', 'rejected', 'Trace entries: 0'], ['accepted', 'rejected', 'Trace entries: 2']),
    14: (['Unknown stop', 'Unknown stop', 'Unknown stop', 'Player starts: 0'], ['Started', 'Unknown stop', 'Invalid volume', 'Player starts: 1']),
    21: (['true false', 'Open after denial: true', 'Open after owner: true', 'Close calls: 0'], ['true false', 'Open after denial: true', 'Open after owner: false', 'Close calls: 1']),
    22: (['false Original', 'false Original', 'false'], ['false Original', 'true Map Key', 'false']),
}

REFERENCE_CASES = {
    13: """
    struct RecordingSink final : NoticeSink {
        std::vector<std::string> calls;
        Delivery deliver(std::string_view line) override {
            calls.emplace_back(line);
            return line == "closed" ? Delivery::Rejected : Delivery::Accepted;
        }
    } sink;
    std::vector<Delivery> inner, outer;
    TracingSink traced(sink, inner), twice(traced, outer);
    assert(twice.deliver("same") == Delivery::Accepted);
    assert(twice.deliver("same") == Delivery::Accepted);
    assert(twice.deliver("closed") == Delivery::Rejected);
    assert((sink.calls == std::vector<std::string>{"same", "same", "closed"}));
    assert((inner == std::vector{Delivery::Accepted, Delivery::Accepted, Delivery::Rejected}));
    assert(inner == outer);
""",
    14: """
    const Catalog catalog{{{"gallery", 0}, {"garden", 9}}};
    Player player;
    AudioGuide guide(catalog, player);
    assert(guide.start("garden", -1) == Launch::InvalidVolume);
    assert(guide.start("missing", 101) == Launch::InvalidVolume);
    assert(catalog.lookups == 0 && player.starts.empty());
    assert(guide.start("missing", 50) == Launch::UnknownStop);
    assert(guide.start("gallery", 0) == Launch::Started);
    assert(guide.start("gallery", 100) == Launch::Started);
    assert(catalog.lookups == 3);
    assert((player.starts == std::vector<std::pair<int, int>>{{0, 0}, {0, 100}}));
""",
    21: """
    static_assert(!std::is_copy_constructible_v<ChannelLease>);
    static_assert(!std::is_move_constructible_v<ChannelLease>);
    static_assert(std::is_nothrow_destructible_v<ChannelLease>);
    OutputChannel channel;
    try {
        const ChannelLease owner(channel);
        assert(owner.acquired() && channel.isOpen());
        {
            const ChannelLease denied(channel);
            assert(!denied.acquired());
        }
        assert(channel.isOpen() && channel.closeCalls() == 0);
        throw 7;
    } catch (int code) {
        assert(code == 7 && !channel.isOpen() && channel.closeCalls() == 1);
    }
    {
        const ChannelLease reacquired(channel);
        assert(reacquired.acquired());
    }
    assert(!channel.isOpen() && channel.closeCalls() == 2);
""",
    22: """
    Board board{{"Old", "Frame"}};
    {
        FrameBatch discarded(board);
        assert(!discarded.commit());
        assert(discarded.append("Uncommitted"));
    }
    assert((board.labels == std::vector<std::string>{"Old", "Frame"}));
    FrameBatch invalid(board);
    assert(invalid.append("New") && invalid.append(""));
    assert(!invalid.commit());
    assert((board.labels == std::vector<std::string>{"Old", "Frame"}));
    FrameBatch accepted(board);
    assert(accepted.append("Map") && accepted.append("Key") && accepted.commit());
    assert(!accepted.commit() && !accepted.append("Later"));
    assert((board.labels == std::vector<std::string>{"Map", "Key"}));
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
