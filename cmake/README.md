
CMake Cross-Compilation Based on Yocto SDK
==========================================

2021-04-02 Alexander Sacharov based on articles by Burkhard Stubert

### General

I have to build embedded Linux with Yocto for a Cortex®-A7 Module based on the LS102xA.
I use Yocto Morty and CMake v3.5.1 (Ubuntu 16.04 LTS).

### Line by line explanation of the CMake toolchain file

We built the embedded Linux system with Yocto. We installed the SDK in `/opt/teledata/2.1.1` by default.
The GCC toolchain, which run on the x86_64-based host computer, is located in `/opt/teledata/2.1.1/sysroots/x86_64-pokysdk-linux`.
The root file system and files needed for cross-builds like headers are located in

`/opt/teledata/2.1.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi.`

We have to set an environment variable `SYSROOTS` to `/opt/teledata/2.1.1/sysroots` such that CMake knows where to find the host and target sysroot.

We must set two environment variables in the Linux shell, in which we want to run CMake and the cross-build later.

```shell
export SYSROOTS=/opt/teledata/2.1.1/sysroots
```

These two environment variables are all we need for cross-compiling with CMake. Especially, we need not run the script `environment-setup-cortexa7hf-neon-poky-linux-gnueabi` to initialise the Yocto-SDK and set two dozen environment variables.

```shell
source environment-setup-cortexa7hf-neon-poky-linux-gnueabi 
```

or

```shell
. environment-setup-cortexa7hf-neon-poky-linux-gnueabi 
```

We are now ready to write the CMake toolchain file. The first two lines set the operating system and architecture of the target system.

```shell
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR armv7-a)
```

Our target system runs on Linux powered by an NXP `LS102xA`, which uses the armv7-a architecture. The variable `CMAKE_SYSTEM_NAME` sets the variable `CMAKE_CROSSCOMPILING` to true.  
We use `CMAKE_CROSSCOMPILING` in CMake files to set variables differently in native and cross builds.

We specify where CMake can find the C and C++ compilers.

```shell
set(TOOLCHAIN_PREFIX $ENV{SYSROOTS}/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
```

If we use an older version of CMake or a different setup, CMake’s compiler check may fail. The reason is that the compiler and linker require special flags like `-mfloat-abi=hard`.  
CMake’s compiler check calls the compiler executables without any flags and there is no way to provide flags.  
If, for example, our toolchain takes advantage of an on-chip floating-point unit (GCC option `-mfloat-abi=hard`), the compiler check produces object files for floating-point emulation  (the default GCC option is `-mfloat-abi=soft`) and fails to link against the “hard” floating-point library.

We have two options to get out this mess. The first option is to set the CMake variable `CMAKE_TRY_COMPILE_TARGET_TYPE`. This skips running the linker, which was exactly the problem in the compiler check. This variable is available from version 3.6.

```shell
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
```

The second option is to switch off the compiler check with the macros from the module `CMakeForceCompiler`. This option is deprecated starting with CMake v3.5, but works for older versions.

```shell
include(CMakeForceCompiler)
CMAKE_FORCE_C_COMPILER(${TOOLCHAIN_PREFIX}gcc GNU)
CMAKE_FORCE_CXX_COMPILER(${TOOLCHAIN_PREFIX}g++ GNU)
```

We can now return to the normal toolchain file. We set the target sysroot CMAKE_SYSROOT as follows.

```shell
set(CMAKE_SYSROOT $ENV{SYSROOTS}/cortexa7hf-neon-poky-linux-gnueabi)
```

CMake adds the option `–sysroot=/opt/teledata/2.1.1/sysroots/cortexa7hf-neon-poky-linux-gnueabi` to every compiler and linker call.

The rest of the toolchain file is pretty smooth sailing.

```shell script
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

The `CMAKE_FIND_ROOT_PATH` tells the CMake find_*() functions to search for programs, libraries and headers in the target sysroot directory `${CMAKE_SYSROOT}`.  
The following three settings restrict the search. `find_program()` is told not to search in the root path. This makes sense, because ARM executables don’t run on the Intel host.  
`find_library()` may only search in the root path and below containing files for the target system. The same is true for find_file and find_path. If we use packages, we should add another line restricting find_package() to the given root path:

```shell script
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
```

The next lines specify the flags for the C and C++ compilers.

```shell script
set(COMPILER_FLAGS " -march=armv7-a -marm -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a9")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILER_FLAGS}" CACHE STRING &quot;" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS}" CACHE STRING "&quot; FORCE)
```

It is important that we force the change of the variables `CMAKE_C_FLAGS` and `CMAKE_CXX_FLAGS` in CMake’s cache. Otherwise, we’ll see the failing compiler checks described above. Of course, you can adapt the `COMPILER_FLAGS` to your own needs.

If the linker needs special flags, we can set them through the variables `CMAKE_EXE_LINKER_FLAGS`, `CMAKE_SHARED_LINKER_FLAGS` and `CMAKE_STATIC_LINKER_FLAGS`. We trust CMake to come up with the right default options for the linker.

Here is the complete toolchain file toolchain-cortexa7hf.cmake under MIT license. Feel free to adapt the toolchain file to your needs and use it in your projects – but keep the license notice.

### Run CMake for application and cross-build

We run CMake for application and cross-build it with the following commands:

```shell script
$ cmake '-GCodeBlocks - Unix Makefiles' -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_CXX_COMPILER:STRING=$SYSROOTS/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++ -DCMAKE_TOOLCHAIN_FILE:FILEPATH=/path/to/toolchain-cortexa7hf.cmake /path/to/project
$ cmake –build . –target all -- -j 12
```
or

```shell script
$ mkdir build
$ cd build
$ conan install .. --build=missing -s build_type=Debug -o *:shared=True ;
```
or

```shell script
$ rm -rf ./* 
$ conan install .. --build=missing -s build_type=Debug -o *:shared=True ;
```
then:

```shell script
$ cmake '-GCodeBlocks - Unix Makefiles' -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_CXX_COMPILER:STRING=$SYSROOTS/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-g++ -DCMAKE_TOOLCHAIN_FILE:FILEPATH=../cmake/toolchain-cortexa7hf.cmake ..
$ cmake --build . --target all -- -j 12
```

Of course, `/path/to/toolchain-cortexa7hf.cmake`, `/path/to/project` and `project` are only placeholders for the toolchain file path, the directory path containing the project’s top-level CMakeLists.txt and the project’s name, respectively.