FROM mcr.microsoft.com/devcontainers/cpp:noble@sha256:a7cddc16b93b4ccfab0d33c805460a826703211ec30e3c04761aec17d71275cb

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
