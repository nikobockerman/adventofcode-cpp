#!/usr/bin/env python

import argparse
import logging
import pathlib
import subprocess
import sys

results = [["day1/day1", "day1/input", "69836"]]


def run(args):
    logging.debug("Running: %s", args)
    result = subprocess.run(args, check=True, capture_output=True, text=True)
    return result.stdout


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument("-x", action="store_true", help="End on first failure")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)

    repo = pathlib.Path(__file__).parent.resolve()
    build = repo / "build" / "clang"

    exit_code = 0
    for data in results:
        prog = data[0]
        expected = data[-1]
        args = data[1:-1]
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
