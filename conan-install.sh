#!/bin/sh

set -e

host_profile=${1:-default}
build_type=${2:-Release}


set -x
poetry run conan install . --update --build=missing \
 -c:h tools.cmake.cmake_layout:build_folder_vars="['settings.compiler']" \
 -pr:h "$host_profile" -pr:b default \
 -s:h build_type="$build_type"
