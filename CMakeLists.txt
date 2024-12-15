cmake_minimum_required(VERSION 3.10)
project(MyNitroProject)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)

add_executable(tests tests.cpp)
include(CTest)
add_test(NAME AllTests COMMAND tests)