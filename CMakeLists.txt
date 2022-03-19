project(ssmhasher)

cmake_minimum_required(VERSION 3.17)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(hash_includes)


add_library(test_gen test_gen.cpp measure.cpp stat.cpp basic_hash.cpp hash_src/MurmurHash1.cpp hash_src/MurmurHash2.cpp hash_src/MurmurHash3.cpp)
add_executable(main main.cpp)
target_link_libraries(main test_gen)
