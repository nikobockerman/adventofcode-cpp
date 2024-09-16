#!/bin/sh

set -eux

if [ -e CMakeUserPresets.json ]; then
    echo "CMakeUserPresets.json already exists."
    echo "Take a look at .devcontainer/CMakeUserPresets.json for prepared presets to use in devcontainer."
    exit 0
fi

cp .devcontainer/CMakeUserPresets.json CMakeUserPresets.json
