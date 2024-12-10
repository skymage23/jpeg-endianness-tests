cmake_minimum_required(VERSION 3.10)
project(jpeg-endianness-tests  CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_compile_options(-std=c++2b -Wall -Wextra -Wpedantic -Werror)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_compile_options(-O0 -g -Wno-error -Lasan)
    )
endif()

find_package(OpenCV REQUIRED)
message(STATUS ${OpenCV_INCLUDE_DIRS})
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

add_library (utilities STATIC utilities.cpp image_utilities.cpp)
target_include_directories(utilities 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

add_library (config STATIC config.cpp)
target_include_directories(config
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

add_executable(opencv_load_jpeg_test ${PROJECT_SOURCE_DIR}/main.cpp)
target_include_directories(opencv_load_jpeg_test  PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(opencv_load_jpeg_test
    ${OpenCV_LIBS}
    utilities
    config
)





add_subdirectory(tests)
