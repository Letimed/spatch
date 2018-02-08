# CMakeLists.txt for spatch
# This file is used to build the project with cmake

# Set cmake minimun version

cmake_minimum_required (VERSION 2.6)

# Set project name

project(spatch)

# The version number.

set (spatch_VERSION_MAJOR 1)
set (spatch_VERSION_MINOR 0)

# Modules directory

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

# Dependencies

find_package(libssh REQUIRED)
find_package(PAM REQUIRED)

# Add includes directories

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(includes LIBSSH_INCLUDE_DIRS PAM_INCLUDE_DIRS)

# Add source files

file(GLOB CORE sources/*.c)

# add the executable

add_executable(spatch ${CORE})

# link libraries

target_link_libraries(spatch ${LIBSSH_LIBRARIES} ${PAM_LIBRARIES})
