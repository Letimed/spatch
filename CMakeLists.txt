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

find_package(LibSSH REQUIRED)
find_package(PAM REQUIRED)

# Add includes directories

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(includes LIBSSH_INCLUDE_DIRS PAM_INCLUDE_DIRS)

# add the executable

add_executable(spatch sources/endpoint.c sources/fs.c sources/group.c sources/list.c
                sources/parser.c sources/sys_auth.c sources/user.c sources/spatch.c)
add_executable(spatch_test sources/endpoint.c sources/fs.c sources/group.c
                sources/list.c sources/parser.c sources/sys_auth.c sources/user.c sources/main.c)
add_executable(respatch sources/endpoint.c sources/fs.c sources/group.c
                sources/list.c sources/parser.c sources/sys_auth.c sources/user.c sources/respatch.c sources/parse_config.c)

# link libraries

target_link_libraries(spatch ${LIBSSH_LIBRARIES} ${PAM_LIBRARIES})
target_link_libraries(spatch_test ${LIBSSH_LIBRARIES} ${PAM_LIBRARIES})
target_link_libraries(respatch ${LIBSSH_LIBRARIES} ${PAM_LIBRARIES})
