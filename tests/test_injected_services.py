"""Build and run the scoped services and creation exercises in both distributed roles."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
LABS = {
    "DPC-07-dpc3-*": ("international", "multiword city"),
    "DPC-08-dpc3-*": ("configured", "zero capacity"),
    "DPC-08-dpc9-*": ("south starts fresh", "intake resumes"),
    "DPC-19-dpc9-*": ("at deadline", "after deadline"),
    "DPC-20-dpc9-*": ("report order", "image isolation"),
}


class InjectionLabs(unittest.TestCase):
    def test_role_contracts(self):
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "lab"
            for pattern, checkpoints in LABS.items():
                folder, = ROOT.glob(pattern)
                for role, expected_exit in [("starter", 1), ("solution", 0)]:
                    with self.subTest(lab=folder.name, role=role):
                        subprocess.run(
                            [os.environ.get("CXX", "c++"), "-std=c++20", "-Wall",
                             "-Wextra", "-Wpedantic", "-Werror", "-fsanitize=address,undefined",
                             "-fno-sanitize-recover=all", str(folder / role / "main.cpp"),
                             "-o", str(executable)], check=True, timeout=45,
                        )
                        run = subprocess.run([executable], capture_output=True, text=True, timeout=5)
                        self.assertEqual(run.returncode, expected_exit, run.stdout + run.stderr)
                        self.assertEqual(run.stderr, "")
                        for checkpoint in checkpoints:
                            self.assertIn(checkpoint + ": observed", run.stdout)
                        print(f"{folder.name}/{role}: exit {run.returncode}\n{run.stdout}")


if __name__ == "__main__":
    unittest.main()
