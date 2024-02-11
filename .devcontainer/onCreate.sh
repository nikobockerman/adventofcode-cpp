#!/bin/sh

set -eux

# Install conan and other project dependencies in order to have conan available
task install:poetry

# Create a default conan profile for this container
poetry run conan profile detect
