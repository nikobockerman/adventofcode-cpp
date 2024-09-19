FROM mcr.microsoft.com/devcontainers/cpp:noble

RUN apt-get update && apt-get install -y \
    libc++-dev \
    software-properties-common \
    && rm -rf /var/lib/apt/lists/*

RUN apt-add-repository -y universe && apt-get update && apt-get install -y \
    clangd \
    clang-format \
    clang-tidy \
    g++-14 \
    shellcheck \
    && rm -rf /var/lib/apt/lists/*
