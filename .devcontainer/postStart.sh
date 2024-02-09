#!/bin/sh

set -eux

poetry install --no-root

if ! poetry run conan profile path default >/dev/null 2>&1 ; then
    poetry run conan profile detect
fi

# Install conan dependencies
./conan-install.sh dev-gcc-12
