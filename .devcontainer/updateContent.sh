#!/bin/sh

set -eux

conan_home="$(conan config home)"
conan_profiles_dir="$conan_home"/profiles

repo=$(readlink -f .)
repo_profiles_dir="$repo"/.devcontainer/conan-profiles
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

task install

for profile in ubuntu-gcc-14-release ubuntu-gcc-14-debug ubuntu-clang-release ubuntu-clang-debug; do
  conan install . \
    --build=missing \
    -pr:h $profile
done

cmake --preset vscode
