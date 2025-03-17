FROM mcr.microsoft.com/devcontainers/cpp:noble@sha256:53f5af4877aaf4c1ee3310f21e0df2ecf0ad6e776910ab3a376f60f2b304a039

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
