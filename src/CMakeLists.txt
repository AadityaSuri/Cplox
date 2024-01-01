# Add core directory
add_subdirectory(core)

# List all source files
set(SOURCE_FILES main.cpp)

# Include core library
add_library(core_lib core/cplox.cpp core/scanner.cpp core/token.cpp)

# Link libraries if there are any
target_link_libraries(core_lib PRIVATE fmt::fmt)
