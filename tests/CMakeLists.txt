#*************************************************
#                 Test Setup Header:             *
#*************************************************
find_program(VALGRIND_BINARY
    NAMES valgrind
    HINTS "/usr/bin" "/usr/local/bin" 
)

if(${VALGRIND_BINARY} STREQUAL "VALGRIND_BINARY-NOTFOUND")
    message(WARNING "Valgrind not found on this system. Disabling Valgrind tests.")
else()
    message(STATUS "Using Valgrind: ${VALGRIND_BINARY}")
endif()


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/googletest)
include(GoogleTest)

#*************************************************
#                  Test Definitions:             *
#*************************************************


#target_link_libraries( unit_tests
#    GTest::gtest_main
#)


#include(GoogleTest)
#gtest_add_tests(
#    TARGET unit_tests
#    TEST_PREFIX "utest_"
#)

#set(UTEST_BINARY "${CMAKE_BINARY_DIR}/tests/unit_tests")


#**************************************************
#                   Memory Checks:                *
#**************************************************
#add_test(valgrind_leak_test
#    COMMAND ${VALGRIND_BINARY} {UTEST_BINARY}
#    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
#)

