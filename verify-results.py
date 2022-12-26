#!/usr/bin/env python

import argparse
import logging
import pathlib
import subprocess
import sys

results = [
    ["day1/d1p1", "day1/input", "69836"],
    ["day1/d1p2", "day1/input", "207968"],
    ["day2/d2p1", "day2/input", "8890"],
    ["day2/d2p2", "day2/input", "10238"],
    ["day3/d3p1", "day3/input", "7848"],
    ["day3/d3p2", "day3/input", "2616"],
    ["day4/d4p1", "day4/input", "536"],
    ["day4/d4p2", "day4/input", "845"],
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
        choices=["clang", "tidy"],
        default="clang",
        nargs="?",
        help="Select flavor for binaries. Default=clang",
    )
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)

    repo = pathlib.Path(__file__).parent.resolve()
    build = repo / "build" / args.flavor

    exit_code = 0
    for data in results:
        prog = data[0]
        expected = data[-1]
        args = ["--quiet"] + data[1:-1]
        print(f"{prog}: ", end="")
        executable = build / prog
        stdout = run([str(executable)] + args)
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
