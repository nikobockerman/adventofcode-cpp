FROM mcr.microsoft.com/devcontainers/cpp:noble@sha256:6493de2f97b96f46c61cedf3f31361c754337db912fd1fd5fc7660b331208df8

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
