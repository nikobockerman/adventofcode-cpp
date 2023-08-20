FROM mcr.microsoft.com/devcontainers/cpp:1-debian-12

# Install additional packages
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends python3-pip

# Allow pip to install packages as system-wide.
# See PEP 668 and Use case 5: https://peps.python.org/pep-0668/#use-cases
RUN rm /usr/lib/python3.11/EXTERNALLY-MANAGED

# Install conan for C++ dependencies
RUN pip install conan==2.*

# Prepare permissions for conan cache
RUN mkdir /conan && chown vscode:vscode /conan
