"""Build the downloadable roles and check their observable event and import contracts."""
import os
from pathlib import Path
import shlex
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]

OBSERVER = """
struct Count : Listener {
    int received = 0;
    void onEvent(const Event&) override { ++received; }
};

struct SubscribeOnce : Listener {
    EventHub& hub;
    std::shared_ptr<Listener> late;
    SubscribeOnce(EventHub& h, std::shared_ptr<Listener> l) : hub(h), late(std::move(l)) {}
    void onEvent(const Event&) override {
        if (late) { hub.subscribe(late); late.reset(); }
    }
};

int main() {
    EventHub hub;
    auto early = std::make_shared<Count>();
    auto late = std::make_shared<Count>();
    auto registration = std::make_shared<SubscribeOnce>(hub, late);
    hub.subscribe(registration);
    hub.subscribe(early);
    hub.publish({"first", 3, ""});
    assert(early->received == 1 && late->received == 0);
    early.reset();
    hub.publish({"second", 4, ""});
    assert(late->received == 1);
    late.reset();
    hub.publish({"quiet", 0, ""});
}
"""

JSON_CASES = r'''
    JsonLinesAdapter adapter;
    const auto records = adapter.import(
        R"({"quantity": 3, "label": "la\"mp", "category": "prop"})" "\r\n"
        R"({"category":"light","quantity":0,"label":"\u2600"})" "\n");
    assert(records.size() == 2 && records[0].label == "la\"mp" &&
           records[0].category == "prop" && records[0].quantity == 3);
    assert(records[1].label == "☀" && records[1].quantity == 0);
    for (const std::string line : {
        R"({"label":"x","category":"p","quantity":"3"})",
        R"({"label":"x","category":"p","quantity":-2})",
        R"({"label":"x","category":"p","quantity":1.5})",
        R"({"label":"x","category":"p","quantity":999999999999})",
        R"({"label":"x","quantity":3})", "{} trailing", "[]", "{"
    }) {
        bool rejected = false;
        try { adapter.import(line); } catch (const std::invalid_argument&) { rejected = true; }
        assert(rejected);
    }
'''

def main():
    with tempfile.TemporaryDirectory() as tmp:
        work = Path(tmp)
        for project in ["DPC3-Observer-Event-Hub", "DPC4-Facade-Adapter-Import-Tool"]:
            for role in ["starter", "solution"]:
                folder = ROOT / project / role
                cpp = (folder / "main.cpp").read_text()
                flags = []
                if project.startswith("DPC3"):
                    check = OBSERVER
                else:
                    build = work / role
                    subprocess.run(["cmake", "-S", str(folder), "-B", str(build)], check=True)
                    subprocess.run(["cmake", "--build", str(build)], check=True)
                    assert "Imported 3 records" in subprocess.check_output([build / "import_records"], text=True)
                    csv = "LegacyCsvAdapter csv{LegacyCsvLoader{}};" if role == "starter" else "LegacyCsvSource csv;"
                    check = 'int main() {\n' + csv + r'''
    const auto recordsFromCsv = csv.import("lamp,prop,3\r\n");
    assert(recordsFromCsv.size() == 1 && recordsFromCsv[0].quantity == 3);
    for (const std::string invalid : {"x,p,3extra", "x,p,3,extra", "x,,2", "x,p,-1", "x,p,"}) {
        bool rejected = false;
        try { csv.import("valid,prop,2\n" + invalid); }
        catch (const std::invalid_argument&) { rejected = true; }
        assert(rejected);
    }
'''
                    if role == "solution":
                        flags = shlex.split(subprocess.check_output(["pkg-config", "--cflags", "--libs", "json-c"], text=True))
                        check += JSON_CASES
                    check += '}\n'
                harness = work / 'case.cpp'
                harness.write_text('#include <cassert>\n' + cpp.split('int main() {')[0] + check)
                exe = work / 'case'
                subprocess.run([os.environ.get("CXX", "c++"), "-std=c++20", "-Wall", "-Wextra",
                                "-Werror", "-pedantic", "-fsanitize=address,undefined",
                                "-fno-sanitize-recover=all", str(harness), "-o", str(exe), *flags], check=True)
                subprocess.run([str(exe)], check=True)
                print("Verified", project, role, flush=True)

if __name__ == "__main__":
    main()
