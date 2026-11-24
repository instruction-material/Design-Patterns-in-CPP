"""Build both published roles and verify the three DPC0 exercise contracts."""

from pathlib import Path
import json
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
LABS = (
    ("DPC-05-dpc0-setup-and-tooling", "title", "Design Patterns", "formatter.cpp", 3),
    ("DPC-01-dpc0-setup-and-tooling-supplemental-2", "temperature_demo", "13.5", "temperature.cpp", 3),
    ("DPC-02-dpc0-setup-and-tooling-supplemental-3", "length_demo", "30", "CMakeLists.txt", 1),
)


class SetupLabTest(unittest.TestCase):
    def test_role_builds_and_completed_exercises(self):
        for folder, program, output, edit, count in LABS:
            for role in ("starter", "solution"):
                with self.subTest(folder=folder, role=role), tempfile.TemporaryDirectory() as temporary:
                    source = Path(temporary) / "source"
                    build = Path(temporary) / "build"
                    shutil.copytree(ROOT / folder / role, source)

                    def configure_and_build():
                        subprocess.run(["cmake", "-S", source, "-B", build, "-DCMAKE_BUILD_TYPE=Debug"], check=True)
                        subprocess.run(["cmake", "--build", build, "--config", "Debug"], check=True)

                    def registered():
                        report = subprocess.check_output(["ctest", "--test-dir", build, "-C", "Debug", "--show-only=json-v1"])
                        return len(json.loads(report)["tests"])

                    def check_tests():
                        return subprocess.run(["ctest", "--test-dir", build, "-C", "Debug", "--output-on-failure"],
                                              text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

                    configure_and_build()
                    if role == "starter":
                        if edit == "CMakeLists.txt":
                            self.assertEqual(registered(), 0)
                        else:
                            self.assertEqual(registered(), count)
                            result = check_tests()
                            self.assertNotEqual(result.returncode, 0, result.stdout)
                            self.assertIn("2 tests failed out of 3", result.stdout)
                        shutil.copyfile(ROOT / folder / "solution" / edit, source / edit)
                        configure_and_build()

                    self.assertEqual(registered(), count)
                    result = check_tests()
                    self.assertEqual(result.returncode, 0, result.stdout)
                    executable = build / program
                    if not executable.is_file():
                        executable = build / "Debug" / program
                    self.assertEqual(subprocess.check_output([executable], text=True).strip(), output)


if __name__ == "__main__":
    unittest.main()
