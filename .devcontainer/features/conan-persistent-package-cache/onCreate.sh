#!/bin/sh

set -e

echo "conan-persistent-package-cache feature: onCreate"

mount_point="/conan-persistent-package-cache"

sudo() {
    if [ "$USER" = "root" ]; then
        "$@"
    else
        command sudo "$@"
    fi
}

sudo chown "$USER":"$USER" "$mount_point"

# Create symlink to persistent cache
mount_point="/conan-persistent-package-cache"
user_conan_dir=$HOME/.conan2
user_conan_cache_dir=$user_conan_dir/p

if [ -d "$user_conan_cache_dir" ]; then
    mv "$user_conan_cache_dir" "$user_conan_cache_dir-old"
else
    mkdir -p "$user_conan_dir"
    chown "$USER":"$USER" "$user_conan_dir"
fi
ln -s "$mount_point" "$user_conan_cache_dir"
