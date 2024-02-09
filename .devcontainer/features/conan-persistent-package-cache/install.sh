# shellcheck shell=sh

set -e

echo "conan-persistent-package-cache feature: Install"
echo "User: ${_REMOTE_USER}"

if [ -z "$_REMOTE_USER" ]; then
    echo "**************************************************************"
    echo "*** Requires _REMOTE_USER to be set (by dev container CLI) ***"
    echo "**************************************************************"
    exit 1
fi

# Prepare on-create script
lifecycle_scripts_dir=/usr/local/share/github-nikobockerman/devcontainer-features/conan-persistent-package-cache
on_create_script=$lifecycle_scripts_dir/onCreate.sh
mkdir -p "$lifecycle_scripts_dir"
cp onCreate.sh "$on_create_script"
chmod +x "$on_create_script"
