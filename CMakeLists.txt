cmake_minimum_required(VERSION 3.10)
project(jpeg-endianness-tests  CXX)

find_package(OpenCV REQUIRED)
message(STATUS ${OpenCV_INCLUDE_DIRS})
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
add_executable(test_runner ${PROJECT_SOURCE_DIR}/main.cpp)

add_executable(opencv_load_jpeg_test ${PROJECT_SOURCE_DIR}/opencv_jpeg.cpp)
target_include_directories(opencv_load_jpeg_test  PRIVATE ${OpenCV_INCLUDE_DIRS})

