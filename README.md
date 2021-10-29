# MyLib

## Requirements

* a C++14 compiler (`gcc-8.3` or above)
* [`cmake`](https://cmake.org) 3.10+
* [`conan`](https://conan.io) 1.28+

## Folder structure and naming conventions

### A root directory

```text
 .
 |- conanfile.txt                # the main `conan` configuration file listing dependencies
 |- cppcheck_suppressions.txt    # optional list of suppressions for cppcheck
 |- CMakeLists.txt               # the main `CMake` Project configuration file
 |- .idea/                       # CLion project files (optional)
 |- .devcontainer                # files how to access (or create) a development container
     |- Dockerfile               # file contains all the commands a user could call on the command line 
     |- conansetup.sh            # conan setup file 
 |- .dockerignore                # files to be excluded by Docker
 |- .gitignore                   # files to be excluded by git
 |-- docs/                       # Documentation files
 |-- cmake/                      # CMake modules and files
 |-  lib/                        # the whole C/C++ project
     |- CMakeLists.txt           # the `CMake` configuration file
     |- src/                     # your library source files
     |- include/mylib            # your library header files
 |-- examples/                   # none automated tests and related samples
 |-- tests/                      # tests (optional for any extra tools or files)
 |-- submodules/                 # submodules
 |-- CONTRIBUTING.md             # contributing rules
 |-- SBOM.md                     # software bill of materials
 |-- LICENSE                     # licence
 |-- README.md                   # this readme
```

> Use *short lowercase names* at least for the *top-level files* and folders except `LICENSE`, `README.md`

### Documentation files

Documentation, referenced data into the project, such as asciidoc, markdown documentation usually stored into the `docs` folder.

```text
 . ...
 |-- doxydoc                 # DoxyGen files
 |-- docs                    # Documentation files (alternatively `doc`)
 |   |-- TOC.md              # Table of contents
 |   |-- faq.md              # Frequently asked questions
 |   |-- misc.md             # Miscellaneous information
 |   |-- usage.md            # Getting started guide
 |   |-- ...                 # etc.
 |-- ...
```

### Source files

The actual source files are stored inside the `project` folder.

```text
 |-  project/                    # the whole C/C++ project
     |- CMakeLists.txt           # the `CMake` configuration file
     |- libname/                 # library files (including CMakeLists.txt, sources)    
         |
         |-- CMakeLists.txt
         |-- include          
         |   |-- libname           
         |       |-- ..          # files *.h*
         |-- src
         |   |-- CMakeLists.txt
         |   |-- *.cpp
         |-- tests
             |-- CMakeLists.txt
             |-- ...
```


### Installation

1. Clone project  from repository.

```shell
git clone git@github.com:dir/libname.git
```


2. Go to project  folder

```shell
cd ./libname
```

### Installation python and conan  (optional, if not installed already)

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

### Build

1. Create directory build

```shell
mkdir cmake-build-debug
cd cmake-build-debug
```

2. Check conan file

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

3. Create new defaults

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

Or edit '~/.conan/profiles/default' and set compiler.libcxx=libstdc++11

************************************************************************************
```

4. Update a setting from a profile located in a custom directory:

```shell
conan profile update settings.compiler.libcxx=libstdc++11 default
```

5. Installs the requirements specified in a recipe conanfile.txt.

```shell
conan install .. --build=missing -s build_type=Debug -o *:shared=True
```

6. Make with  cmake

```shell
cmake ..
make
```

