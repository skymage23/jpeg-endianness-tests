#include <cstdint>
#include <cstdlib>
#include <format>
#include <memory>
#include <cstdarg>

#include <gtest/gtest.h>

#include <initialization/error_handling/basic_error_handling.hpp>

namespace {
    std::shared_ptr<std::string> invoke_generate_error_string(
            unsigned int errcode,
            std::string prefix,
            ...
    ) {
        va_list args;
        va_start(args, prefix);
        return cnn_practice::initialization::error_handling::generate_error_string(
            errcode,
            prefix,
            args
        );
    }
};

TEST(
    test_basic_error_handling,
    test_basic_error_handling_catch_errcode_too_high
){
    //Hello:
    unsigned int test_errcode = UINT32_MAX;
    std::shared_ptr<std::string> err_str = invoke_generate_error_string( 
        test_errcode,
        "TEST" 
    );

    ASSERT_EQ(err_str, nullptr);
}

TEST(
    test_basic_error_handling,
    test_basic_error_handling_die_on_invalid_errcode 
) {
    auto test_code = [](){
        unsigned int test_errcode = UINT32_MAX;
        cnn_practice::initialization::error_handling::fatal(test_errcode);
    };

    EXPECT_EXIT(
        test_code(),
        testing::ExitedWithCode(EXIT_FAILURE),
        std::format("FATAL: Invalid errcode: {}", UINT32_MAX)
    );
}


TEST(
    test_basic_error_handling,
    test_basic_error_handling_test_warn_pivot_to_fatal 
) {
    EXPECT_DEATH(
        {
            unsigned int test_errcode = UINT32_MAX;
            cnn_practice::initialization::error_handling::warn(test_errcode);
            exit(EXIT_SUCCESS);
        },
        std::format("FATAL: Invalid errcode: {}", UINT32_MAX)
    );
}


TEST(
    test_basic_error_handling,
    test_basic_error_handling_test_debug_pivot_to_fatal 
) {
    EXPECT_DEATH(
        {
            unsigned int test_errcode = UINT32_MAX;
            cnn_practice::initialization::error_handling::debug(test_errcode);
            exit(EXIT_SUCCESS);
        },
        std::format("FATAL: Invalid errcode: {}", UINT32_MAX)
    );
}