import subprocess
import logging
from typing import Any, Iterable

logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.DEBUG)


def run(
    cmd: list[str], *, capture_output: bool = False, text: bool = False
) -> subprocess.CompletedProcess[Any]:
    logging.debug(f"Run: {cmd}")
    return subprocess.run(cmd, check=True, capture_output=capture_output, text=text)


def _get_workflow_presets() -> Iterable[str]:
    for line in run(
        ["cmake", "--workflow", "--list-presets"], capture_output=True, text=True
    ).stdout:
        yield line.split(maxsplit=1)[0].strip(' "')


def main():
    workflow_presets = _get_workflow_presets()
    for preset in workflow_presets:
        run(["cmake", "--workflow", "--preset", preset])


if __name__ == "__main__":
    main()
