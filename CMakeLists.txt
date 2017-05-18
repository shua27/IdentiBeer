cmake_minimum_required(VERSION 3.7)
project(untitled1)

include_directories(${src})


set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)
add_executable(CapTure ${SOURCE_FILES})