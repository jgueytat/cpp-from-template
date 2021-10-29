
set(TargetName mylib)

add_library(${TargetName} SHARED)

target_compile_features(${TargetName} PRIVATE cxx_std_11)
target_include_directories (${TargetName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Compilation Flags
target_compile_options(${TargetName} PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Sources
target_sources( ${TargetName} PRIVATE
        src/foo.cpp )

set_target_properties(${TargetName} PROPERTIES PUBLIC_HEADER "${INCLUDE_FILES}")
        
# Install
install(TARGETS ${TargetName}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION include/${TargetName})
