#!/bin/sh

set -eux

# Install conan and other project dependencies
task install:poetry

# Setup conan profiles specific for this devcontainer
conan_profiles_dir=$HOME/.conan2/profiles
repo_profiles_dir=$(readlink -f .devcontainer/conan-profiles)
mkdir -p "$conan_profiles_dir"
for repo_profile_path in "$repo_profiles_dir"/*; do
    profile_name=$(basename "$repo_profile_path")
    symlink="$conan_profiles_dir"/"$profile_name"
    target="$repo_profiles_dir"/"$profile_name"
    if [ -e "$symlink" ]; then
        if [ -L "$symlink" ] && [ "$(readlink "$symlink")" = "$target" ]; then
            continue
        fi
        rm -rf "$symlink"
    fi
    ln -s "$target" "$symlink"
done

# Install conan dependencies
task PROFILE=dev-clang-17 \
    install:conan BUILD_TYPE=Debug \
    install:conan BUILD_TYPE=Release
