# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.158.0/containers/ubuntu/.devcontainer/base.Dockerfile

# [Choice] Ubuntu version: bionic, focal
ARG VARIANT="focal"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

# ** [Optional] Uncomment this section to install additional packages. **
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
      # Helpers for completion in terminal
      bash-completion \
      # LLVM-based compiler-suite, stdlib + helpers for integration in IDE
      clang \
      clang-tools \
      clangd \
      libc++-dev \
      libc++abi-dev \
      # CMake
      cmake \
      # Code Analyzer
      cppcheck \
      # Code documentation tool
      doxygen \
      # Linux "file"-command, used for file-type determination
      file \
      # Required by doxygen for generation of graphs
      graphviz \
      # LLVM-based debugger
      lldb-9 \
      # Make
      make \
      # Python3, required for installing "Conan package-manager"
      python3-pip \
      python3-setuptools \
      # Vim
      vim

RUN pip3 install conan cpplint --no-cache-dir
