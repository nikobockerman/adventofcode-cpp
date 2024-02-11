import subprocess
from typing import Any, Iterable


def run(
    cmd: list[str], *, capture_output: bool = False, text: bool = False
) -> subprocess.CompletedProcess[Any]:
    print(f"Run: {cmd}")
    return subprocess.run(cmd, check=True, capture_output=capture_output, text=text)


def parse_preset_name_lines(output: str) -> Iterable[str]:
    for line in (line.strip() for line in output.strip().splitlines()):
        if not line or line.startswith("Available "):
            continue
        yield line


def parse_preset_names(output: str) -> Iterable[str]:
    for line in parse_preset_name_lines(output):
        yield line.strip(' "')


def filter_presets(presets: Iterable[str]) -> Iterable[str]:
    for preset in presets:
        if not preset.startswith("MSVC"):
            continue
        yield preset


def main():
    build_presets = filter_presets(
        parse_preset_names(
            run(
                ["cmake", "--build", "--list-presets"], capture_output=True, text=True
            ).stdout
        )
    )
    for preset in build_presets:
        run(["cmake", "--build", "--preset", preset, "-v"])

    test_presets = filter_presets(
        parse_preset_names(
            run(["ctest", "--list-presets"], capture_output=True, text=True).stdout
        )
    )
    for preset in test_presets:
        run(["ctest", "--preset", preset])


if __name__ == "__main__":
    main()
