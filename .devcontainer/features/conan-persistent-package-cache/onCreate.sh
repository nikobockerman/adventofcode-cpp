#!/bin/sh

set -e

echo "conan-persistent-package-cache feature: onCreate"

mount_point="/conan-persistent-package-cache"
user_conan_dir=$HOME/.conan2
user_conan_cache_dir=$user_conan_dir/p


sudo() {
    if [ "$USER" = "root" ]; then
        "$@"
    else
        command sudo "$@"
    fi
}

# Prepare mounted volume permissions
sudo chown "$USER":"$USER" "$mount_point"

# Rename theoretical old conan cache directory
if [ -d "$user_conan_cache_dir" ]; then
    mv "$user_conan_cache_dir" "$user_conan_cache_dir-old"
fi

# Create new conan cache directory as symlink to the mounted volume
mkdir -p "$user_conan_dir"
chown "$USER":"$USER" "$user_conan_dir"
ln -s "$mount_point" "$user_conan_cache_dir"
chown -h "$USER":"$USER" "$user_conan_cache_dir"
