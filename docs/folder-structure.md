
Folder structure and naming conventions
=======================================

## Naming conventions

Use *short lowercase names* at least for the *top-level files* and folders except `LICENSE`, `README.md`

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

