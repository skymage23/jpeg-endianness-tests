cmake_minimum_required(VERSION 3.10)
project(jpeg-endianness-tests  CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_compile_options(-std=c++2b -Wall -Wextra -Wpedantic -Werror)


find_package(OpenCV REQUIRED)
message(STATUS ${OpenCV_INCLUDE_DIRS})
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)


add_executable(opencv_load_jpeg_test ${PROJECT_SOURCE_DIR}/opencv_jpeg.cpp)
target_include_directories(opencv_load_jpeg_test  PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(opencv_load_jpeg_test
    ${OpenCV_LIBS}
)


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(opencv_load_jpeg_test
        PRIVATE -O0   #May want to move this outside CMake.
        PRIVATE -g
        PRIVATE -Wno-error
        #PRIVATE -fsanitize=address
        #PRIVATE -fsanitize=leak
        PRIVATE -Lasan
    )
endif()


add_subdirectory(tests)
