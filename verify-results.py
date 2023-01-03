#!/usr/bin/env python

import argparse
import logging
import pathlib
import platform
import subprocess
import sys

results = [
    ["day1", "d1p1", "69836"],
    ["day1", "d1p2", "207968"],
    ["day2", "d2p1", "8890"],
    ["day2", "d2p2", "10238"],
    ["day3", "d3p1", "7848"],
    ["day3", "d3p2", "2616"],
    ["day4", "d4p1", "536"],
    ["day4", "d4p2", "845"],
    ["day5", "d5p1", "TLFGBZHCN"],
]


def run(args):
    logging.debug("Running: %s", args)
    result = subprocess.run(args, check=True, capture_output=True, text=True)
    return result.stdout


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument("-x", action="store_true", help="End on first failure")
    parser.add_argument(
        "flavor",
        default="vscompiler",
        nargs="?",
        help="Select flavor for binaries (directory name under build/). "
        "Default=vscompiler",
    )
    parser.add_argument(
        "build_type",
        default="",
        nargs="?",
        help="Select CMake build type for binaries (Debug, Release, etc.). "
        "Used for multi-configuration CMake variants to choose correct build "
        "directory",
    )
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)

    repo = pathlib.Path(__file__).parent.resolve()
    build = repo / "build" / args.flavor

    exit_code = 0
    for data in results:
        dir = data[0]
        prog = data[1]
        expected = data[-1]
        arguments = ["--quiet", str(build / dir / "input")]
        print(f"{prog}: ", end="")
        executable = build / dir
        if args.build_type:
            executable = executable / args.build_type
        executable = executable / prog
        if platform.system() == "Windows":
            executable = executable.with_suffix(".exe")
        stdout = run([str(executable)] + arguments)
        result = stdout.splitlines()[-1].strip()
        logging.debug("Result:   %s", result)
        logging.debug("Expected: %s", expected)
        success = result == expected
        if success:
            print("pass")
        else:
            print("FAIL")
            exit_code = 1
            break

    sys.exit(exit_code)


if __name__ == "__main__":
    main()
