find_package(OpenCV REQUIRED)
message(STATUS ${OpenCV_INCLUDE_DIRS})

add_subdirectory(initialization)
add_subdirectory(error_handling)

add_library (utilities STATIC 
    ${PROJECT_SOURCE_DIR}/utilities.cpp
    ${PROJECT_SOURCE_DIR}/image_utilities.cpp
)
target_include_directories(utilities 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

add_library (config STATIC
    ${PROJECT_SOURCE_DIR}/config.cpp
)
target_include_directories(config
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

