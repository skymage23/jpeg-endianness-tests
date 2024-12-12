add_executable(test_basic_error_handling
    ${CMAKE_CURRENT_LIST_DIR}/test_basic_error_handling.cpp
)

target_include_directories(test_basic_error_handling
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

add_dependencies(test_basic_error_handling
    initialization_error_handling
)

#target_compile_options(test_basic_error_handling
#  PRIVATE -L${PROJECT_BINARY_DIR}/src/initialization/error_handling
#  PRIVATE -linitialization_error_handling
#)

target_link_libraries(test_basic_error_handling
   PUBLIC initialization_error_handling
   PUBLIC GTest::gtest_main
)

gtest_add_tests(
    TARGET test_basic_error_handling
    TEST_PREFIX "test_basic_error_handling_"
)
