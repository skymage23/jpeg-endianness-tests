add_executable(test_basic_error_handling
    ${CMAKE_CURRENT_LIST_DIR}/tests_basic_error_handling.cpp
)

target_link_libraries(test_basic_error_handling
   GTest::gtest_main
)

gtest_add_tests(
    TARGET test_basic_error_handling
    TEST_PREFIX "test_basic_error_handling_"
)