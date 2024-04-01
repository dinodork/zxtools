project(ZXTools)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
add_subdirectory(data)
add_subdirectory(src)
