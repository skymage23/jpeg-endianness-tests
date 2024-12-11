add_library(initialization_error_handling STATIC
    ${CMAKE_CURRENT_LIST_DIR}/error_handling.cpp
)

target_include_directories(initialization_error_handling
    ${PROJECT_SOURCE_DIR}/include
)