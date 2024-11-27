cmake_minimum_required(VERSION 3.10)
project(jpeg-endianness-tests  CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_compile_options(-std=c++2b -Wall -Wextra -Wpedantic -Werror)


find_package(OpenCV REQUIRED)
message(STATUS ${OpenCV_INCLUDE_DIRS})
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
add_executable(test_runner ${PROJECT_SOURCE_DIR}/main.cpp)

add_library(trie STATIC ${PROJECT_SOURCE_DIR}/trie.cpp)
target_include_directories(trie 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/internal/include    
)

#if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
#    target_compile_options(trie
#        PRIVATE -O0   #May want to move this outside CMake.
#        PRIVATE -g
#        PRIVATE -fsanitize=address
#        PRIVATE -fsanitize=leak
#        PRIVATE -Lasan
#    )
#endif()


add_executable(opencv_load_jpeg_test ${PROJECT_SOURCE_DIR}/opencv_jpeg.cpp)
target_include_directories(opencv_load_jpeg_test  PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(opencv_load_jpeg_test
    trie
)

add_subdirectory(tests)
