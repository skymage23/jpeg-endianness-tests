add_library(initialization STATIC
    ${PROJECT_SOURCE_DIR}/initialization/initialization.cpp
)
target_include_directories(initialization
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)