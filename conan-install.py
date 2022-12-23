#!/usr/bin/env python

import argparse
import logging
import pathlib
import subprocess


def run_cmd(args):
    logging.debug("Running cmd: %s", args)
    subprocess.run(args, check=True)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", action="store_true")
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)

    repo = pathlib.Path(__file__).parent.resolve()
    conan_install_dir = repo / "conan-install"
    # conan_install_dir.parent.mkdir(exist_ok=True)
    run_cmd(
        [
            "conan",
            "install",
            "--update",
            f"--output-folder={str(conan_install_dir)}",
            f"--install-folder={str(conan_install_dir)}",
            "--build=missing",
            str(repo),
        ]
    )


if __name__ == "__main__":
    main()
