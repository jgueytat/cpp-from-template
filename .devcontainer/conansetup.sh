#!/usr/bin/env bash

set -e

WORKSPACE=..
BUILDTYPE=Debug
if [ ! -z "$GITHUB_WORKSPACE" ]; then
WORKSPACE="$GITHUB_WORKSPACE"
fi
if [ ! -z "$BUILD_TYPE" ]; then
BUILDTYPE="$BUILD_TYPE"
fi

if [ -e $1 ] || [ $1 != "--installonly" ]; then
#Setup conan - create profile and switch to c++11 to prevent linker-errors in shared-libs
conan profile new default --detect
conan profile update settings.compiler.libcxx=libc++
conan profile update settings.compiler.cppstd=gnu17
fi

mkdir -p build
cd build
conan install $WORKSPACE --build=missing -s build_type=$BUILDTYPE -o *:shared=True
cmake $WORKSPACE -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$BUILDTYPE
