project(ssmhasher)

cmake_minimum_required(VERSION 3.17)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(test_gen test_gen.cpp measure.cpp stat.cpp)
add_executable(main main.cpp)
target_link_libraries(main test_gen)
