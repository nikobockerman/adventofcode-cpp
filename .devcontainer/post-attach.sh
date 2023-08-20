#!/bin/bash

set -eux

conan_home=${CONAN_HOME:-$HOME/.conan2}

cp .devcontainer/conan-profiles/dev-gcc-12 "$conan_home"/profiles/
./conan-install.sh dev-gcc-12
