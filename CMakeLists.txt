cmake_minimum_required(VERSION 3.24)
project(project3)

set(CMAKE_CXX_STANDARD 17)

add_executable(project3 main.cpp local.h main2.cpp main1.cpp test.cpp)
