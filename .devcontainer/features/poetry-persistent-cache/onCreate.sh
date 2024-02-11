#!/bin/sh

set -e

echo "poetry-persistent-cache feature: onCreate"

mount_point="/poetry-persistent-cache"

sudo() {
    if [ "$USER" = root ]; then
        "$@"
    else
        command sudo "$@"
    fi
}

# Prepare mounted volume permissions
sudo chown "$USER":"$USER" "$mount_point"
