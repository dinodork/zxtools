add_executable(bokstav bokstav.cpp)

target_include_directories(bokstav PUBLIC "${CMAKE_SOURCE_DIR}"
                                          "${CMAKE_SOURCE_DIR}/include")

target_include_directories(bokstav PUBLIC "${KOKKOS_MDSPAN_HOME}")
target_compile_features(bokstav PRIVATE cxx_std_23)

add_executable(kerning kerning.cpp)
