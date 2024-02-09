#!/bin/sh

set -eux

echo "devcontainer: onCreate"

conan_config_dir=$HOME/.conan2
conan_profile_dir=$conan_config_dir/profiles

# Prepare a specific conan profile for this container
repo_profiles=$(readlink -f .devcontainer/conan-profiles)
profile=dev-gcc-12
mkdir -p "$conan_profile_dir"
ln -s "$repo_profiles"/"$profile" "$conan_profile_dir"/"$profile"
