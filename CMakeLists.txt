cmake_minimum_required(VERSION 3.20)
project(Huawei_Challenge_Rule_Matching)

set(CMAKE_CXX_STANDARD 11)
add_compile_definitions(LOCAL)
add_executable(Main main.cpp)
add_executable(BF brute_force.cpp)
add_executable(Check check.cpp)