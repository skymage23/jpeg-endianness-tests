#include <cstdint>
#include <memory>

#include <gtest/gtest.h>

#include <initialization/error_handling/basic_error_code_handlings.hpp>

TEST(
    test_basic_error_handling,
    test_basic_error_handling_catch_errcode_too_high
){
    //Hello:
    int test_errcode = INT32_MAX;
    std::unique_ptr<std::string> err_str = 
        cnn_practice::initialization::error_handling::generate_error_string( 
        test_errcode,
        "TEST" 
    );

    ASSERT_EQ(err_str, nullptr);
}
