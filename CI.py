import subprocess


def run(cmd, **kwargs):
    print(f"Run: {cmd}")
    return subprocess.run(cmd, check=True, **kwargs)


def parse_preset_name_lines(output):
    lines = [line.strip() for line in output.strip().splitlines()]
    return [
        line.strip() for line in lines if line and not line.startswith("Available ")
    ]


def parse_preset_names(output):
    lines = parse_preset_name_lines(output)
    return [l.strip(' "') for l in lines]


def filter_presets(presets):
    return [p for p in presets if any([p.startswith(prefix) for prefix in ["MSVC"]])]


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
