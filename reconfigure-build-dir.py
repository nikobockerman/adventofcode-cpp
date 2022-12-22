#!/usr/bin/env python

import argparse
import logging
import os
import pathlib
import shutil
import subprocess


def run_cmd(args, **kwargs):
    logging.info("Running cmd: %s", args)
    logging.debug(f"With kwargs: {kwargs}")
    subprocess.run(args, check=True, **kwargs)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument(
        "flavor",
        choices=["clang", "tidy"],
        default="clang",
        nargs="?",
        help="Select build flavor. Default=clang",
    )
    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)

    repo = pathlib.Path(__file__).parent.resolve()
    build_dir = repo / "build" / args.flavor
    toolchain = repo / "conan-install" / "conan_toolchain.cmake"

    if build_dir.exists():
        logging.debug("Removing existing build dir")
        shutil.rmtree(build_dir)

    env = os.environ.copy()
    flags = "-Wall -Wextra"
    env["CFLAGS"] = flags
    env["CXXFLAGS"] = flags
    cmd_args = []
    if args.flavor == "clang":
        env["CC"] = "clang-13"
        env["CXX"] = "clang++-13"
    elif args.flavor == "tidy":
        cmd_args += ["-DCMAKE_CXX_CLANG_TIDY=clang-tidy-13"]

    build_dir.parent.mkdir(exist_ok=True)
    run_cmd(
        [
            "cmake",
            "-S",
            ".",
            "-B",
            build_dir,
            "-DCMAKE_BUILD_TYPE=Debug",
            "-DCMAKE_MAP_IMPORTED_CONFIG_DEBUG=Release",
            f"-DCMAKE_TOOLCHAIN_FILE={str(toolchain)}",
            "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
        ]
        + cmd_args,
        env=env,
    )


if __name__ == "__main__":
    main()
