cmake_minimum_required(VERSION 3.0)
project(Cplox)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif()

find_package(fmt CONFIG REQUIRED)


# Add subdirectories
add_subdirectory(src)
add_subdirectory(include)

# Specify the executable
add_executable(cplox src/main.cpp)

target_include_directories(cplox
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)
target_include_directories(core_lib
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)


# Link libraries (if any)
#target_link_libraries(cplox PRIVATE fmt::fmt)
target_link_libraries(cplox PRIVATE core_lib)
target_link_libraries(cplox PRIVATE fmt::fmt)

