# Requirements

* a C++11 compiler (`gcc-6.3` or above)
* [`cmake`](https://cmake.org) 3.10+
* [`conan`](https://conan.io) 1.28+
* `cppcheck` (optional)


## Clone project from repository

1. Clone project from repository.

```shell
git clone git@github.com:mylib.git mylib
```


2. Go to project folder

```shell
cd mylib
```

## Installation python and conan  (optional, if not installed)

1. Install python3

```shell
sudo apt-get install  python3-pip
```

2. Install conan

```shell
pip3 install conan
```

3. Export PATH

```shell
export PATH=$PATH:/home/user_name/.local/bin
```

4. Check conan file

```shell
cat ../.devcontainer/conansetup.sh

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

#Setup conan - create profile and switch to c++11 to prevent linker-errors in shared-libs
conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default

mkdir -p build
cd build
conan install $WORKSPACE --build=missing -s build_type=$BUILDTYPE -o *:shared=True
cmake $WORKSPACE -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$BUILDTYPE
```


5. Create new defaults

```shell
$ conan profile new default --detect

Found gcc 6.3
Found clang 9.0
gcc>=5, using the major as version

************************* WARNING: GCC OLD ABI COMPATIBILITY ***********************

Conan detected a GCC version > 5 but has adjusted the 'compiler.libcxx' setting to
'libstdc++' for backwards compatibility.
Your compiler is likely using the new CXX11 ABI by default (libstdc++11).

If you want Conan to use the new ABI for the default profile, run:

   $ conan profile update settings.compiler.libcxx=libstdc++11 default

Or edit '/home/alexander/.conan/profiles/default' and set compiler.libcxx=libstdc++11

************************************************************************************
```

6. Update a setting from a profile located in a custom directory:

```shell
conan profile update settings.compiler.libcxx=libstdc++11 default
```

### Build

1. Create directory build

```shell
mkdir build
cd build
```

2. Installs the requirements specified in a recipe conanfile.txt.

```shell
conan install .. --build=missing -s build_type=Debug -o *:shared=True
```

3. Make with  cmake

```shell
cmake ..
make
```

