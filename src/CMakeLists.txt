add_executable(bokstav bokstav.cpp)

target_include_directories(bokstav PUBLIC ${CMAKE_SOURCE_DIR}
                                          ${CMAKE_SOURCE_DIR}/include)

target_compile_features(bokstav PRIVATE cxx_std_23)
