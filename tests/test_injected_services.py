"""Build and run each dependency-injection exercise in both distributed roles."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
LABS = {
    "08": ("south starts fresh", "intake resumes"),
    "19": ("at deadline", "after deadline"),
    "20": ("report order", "image isolation"),
}


class InjectionLabs(unittest.TestCase):
    def test_role_contracts(self):
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "lab"
            for prefix, checkpoints in LABS.items():
                folder, = ROOT.glob(f"DPC-{prefix}-dpc9-*")
                for role, expected_exit in [("starter", 1), ("solution", 0)]:
                    with self.subTest(lab=prefix, role=role):
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
