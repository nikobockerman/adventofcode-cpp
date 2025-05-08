FROM mcr.microsoft.com/devcontainers/cpp:noble@sha256:a74f174cf8541b418e50787382d0edb5cd2b817754da2eaf892bae3468a62264

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
