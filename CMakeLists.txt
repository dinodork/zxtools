cmake_minimum_required(VERSION 3.22)

project(ZXTools)

option(KOKKOS_MDPSAN_HOME "Path to Kokkos mdspan")

if("${KOKKOS_MDSPAN_HOME}" STREQUAL "OFF")
  message(FATAL_ERROR "KOKKOS_MDSPAN_HOME not set!")
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

add_subdirectory(data)
add_subdirectory(src)
