project(ssmhasher)

cmake_minimum_required(VERSION 3.17)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(hash_includes)
add_compile_options("-DXXH_INLINE_ALL")

add_compile_options(-O2)

add_executable(main main.cpp 
    test_gen.cpp
    measure.cpp
    stat.cpp
    basic_hash.cpp
    hash_src/MurmurHash1.cpp
    hash_src/MurmurHash2.cpp
    hash_src/MurmurHash3.cpp
)

