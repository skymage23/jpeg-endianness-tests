cmake_minimum_required(VERSION 3.10)
project(jpeg-endianness-tests  CXX)
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
add_executable(test_runner ${PROJECT_SOURCE_DIR}/main.cpp)
