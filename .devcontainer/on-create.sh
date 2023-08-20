#!/bin/bash

set -eux

# Set permissions for CONAN_HOME
sudo chown -R "$USER":"$USER" "$CONAN_HOME"

# Prepare conan default profile
conan profile detect

# Configure git for line-endings
git config --global core.autocrlf input
