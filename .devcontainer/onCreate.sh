#!/bin/sh

set -eux

yarn
yarn dlx @yarnpkg/sdks vscode

repo=$(readlink -f .)
conan_home="$(conan config home)"
rm "$conan_home"/global.conf
ln -s "$repo"/.devcontainer/conan-global.conf "$conan_home"/global.conf
conan profile detect

if [ -e CMakeUserPresets.json ]; then
  echo "CMakeUserPresets.json already exists."
  echo "Take a look at .devcontainer/CMakeUserPresets.json for prepared presets to use in devcontainer."
else
  cp .devcontainer/CMakeUserPresets.json CMakeUserPresets.json
  echo "Prepared CMakeUserPresets.json for devcontainer. That file is meant to be enhanced by you and won't be overwritten."
fi

if [ -e compile_commands.json ]; then
  echo "compile_commands.json already exists."
  echo "Devcontainer would by default set compile_commands.json as symlink to build/clang/vscode/compile_commands.json."
else
  ln -s build/clang/vscode/compile_commands.json compile_commands.json
  echo "compile_commands.json symlinked to build/clang/vscode/compile_commands.json."
fi
