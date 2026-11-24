"""Verify the shipped projects, a completed starter, and observable CLI contracts."""
from pathlib import Path
import shutil
import subprocess
import tempfile

LAB = Path(__file__).resolve().parents[1] / "DPC-09-dpc12-capstone-studio"


def run(args, *, text="", expected=0):
    result = subprocess.run(args, input=text, text=True, capture_output=True, timeout=60)
    if result.returncode != expected:
        raise AssertionError((args, expected, result.stdout, result.stderr))
    return result


def verify(src, build, completed):
    run(["cmake", "-S", src, "-B", build, "-DBUILD_TESTING=ON",
         "-DCMAKE_CXX_FLAGS=-Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-sanitize-recover=all"])
    run(["cmake", "--build", build, "--parallel", "2"])
    for case in ["standard", "malformed", "limit", "isolation", "comma", "mixed"]:
        passing = completed or case not in ("comma", "mixed")
        result = run(["ctest", "--test-dir", build, "-R", "^" + case + "$", "--output-on-failure"],
                     expected=0 if passing else 8)
        if case not in result.stdout or (not passing and f"Failed: {case}" not in result.stdout):
            raise AssertionError(result.stdout)
    cli = build / "asset_import"
    assert run([cli, "space"], text="tile 2\nhero 1\ntile 3\n").stdout == "hero=1\ntile=5\n"
    broken = run([cli, "space"], text="hero 5\ntile nope", expected=1)
    assert broken.stdout == "" and broken.stderr == "Invalid batch\n"
    assert run([cli, "unknown"], expected=2).stderr.startswith("Usage:")
    result = run([cli, "comma"], text="tile,2\nhero,1\ntile,3\n", expected=0 if completed else 1)
    assert result.stdout == ("hero=1\ntile=5\n" if completed else "")
    print(src.name, "six CTest outcomes and four CLI scenarios matched")


if __name__ == "__main__":
    with tempfile.TemporaryDirectory() as directory:
        work = Path(directory)
        verify(LAB / "starter", work / "initial-build", False)
        verify(LAB / "solution", work / "reference-build", True)
        completed = work / "completed-starter"
        shutil.copytree(LAB / "starter", completed)
        shutil.copyfile(LAB / "solution/importer.cpp", completed / "importer.cpp")
        verify(completed, work / "completed-build", True)
