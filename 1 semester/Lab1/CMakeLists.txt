cmake_minimum_required(VERSION 3.15)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1 main.cpp src/Random.cpp src/Random.h src/Sort.h "src/Multiphase sort.cpp" "src/Multiphase sort.h" src/Sort.cpp)