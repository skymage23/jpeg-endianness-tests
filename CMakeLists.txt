cmake_minimum_required(VERSION 3.10)
project(jpeg-endianness-tests  CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)


add_compile_options(-std=c++2b -Wall -Wextra -Wpedantic -Werror)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_compile_options(-O0 -g -Wno-error -Lasan)
        
endif()



#add_library(initialization 
#    ${PROJECT_SOURCE_DIR}/initialization/*
#)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(opencv_load_jpeg_test ${PROJECT_SOURCE_DIR}/main.cpp)
target_include_directories(opencv_load_jpeg_test  PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(opencv_load_jpeg_test
    ${OpenCV_LIBS}
    initialization
    utilities
    config
)


