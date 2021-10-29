
# CMakefile.txt: tests/CMakeLists.txt
# Project: Template
# Date: 2021
# Author: (AS) Alexander Sacharov <a.sacharov@gmx.de> (alexander)
#
# Notes:

enable_testing()

# Set project name
set(TargetName mylibtest)

set(LIBS
        pthread
        rt
        )

# Pre-defines standard install locations on *nix systems.
include(GNUInstallDirs)

add_executable( ${TargetName} )
target_sources(${TargetName} PRIVATE "test_main.cpp" "test_cases.cpp" )
target_link_libraries(${TargetName} PUBLIC ${LIBS} ${CONAN_LIBS_SPDLOG} )
target_compile_features(${TargetName} PRIVATE cxx_std_17)

install(TARGETS ${TargetName} DESTINATION bin)
