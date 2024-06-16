#!/usr/bin/env python3

import os
import subprocess
import sys

def run_command(command, cwd=None):
    """Run a system command and exit on failure."""
    result = subprocess.run(command, shell=True, cwd=cwd)
    if result.returncode != 0:
        print(f"Command failed with exit code {result.returncode}: {command}")
        sys.exit(result.returncode)

def main():
    project_dir = os.path.dirname(os.path.abspath(__file__))
    build_dir = os.path.join(project_dir, 'build')

    # Step 1: Run CMake to configure the project
    run_command('cmake -S . -B build', cwd=project_dir)

    # Step 2: Build the project
    run_command('cmake --build build', cwd=project_dir)

    # Step 3: Run the tests
    run_command('ctest --output-on-failure', cwd=build_dir)

if __name__ == "__main__":
    main()