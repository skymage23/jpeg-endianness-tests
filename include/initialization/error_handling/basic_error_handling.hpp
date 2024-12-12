#ifndef JPEG_ENDIANNESS_TESTS_INCLUDE_INITIALIZATION_ERROR_HANDLING_BASIC_ERROR_HANDLING
#define JPEG_ENDIANNESS_TESTS_INCLUDE_INITIALIZATION_ERROR_HANDLING_BASIC_ERROR_HANDLING

#include <memory>
#include <string>

namespace cnn_practice {
    namespace initialization {
        namespace error_handling {
            #define ERRCODE_MIN           0

            //If you add new errcodes, increment this value by
            //one for each errcode you add.
            #define ERRCODE_MAX           6
            #define SUCCESS               0
            #define INVALID_ERRCODE       1 
            #define OUT_OF_MEMORY         2
            #define UNRECOGNIZED_ARGUMENT 3
            #define TOO_FEW_ARGUMENTS     4
            #define TOO_MANY_ARGUMENTS    5
            #define FILE_WRITE_ERROR      6
            //int file_read_error = 6;


            std::string generate_string__success();
            std::string generate_string__invalid_errcode();
            std::string generate_string__out_of_memory();
            std::string generate_string__unrecognized_argument(); 
            std::string generate_string__too_many_arguments();
            std::string generate_string__too_few_arguments();
            std::string generate_string__file_write_error();

            //Given an errcode, produces the associated message string.
            //Some errcodes require additional arguments.
            //
            //Convention: Any errcodes requiring additional arguments must
            //            be denoted in the case statement by adding "//variadic"
            //            as a comment at the top of the associated case block.
            //
            //This is so it is easy to identify argument errors in the function in
            //case the coder who wrote the beginnings of the case statement
            //has moved on to another part of the code before they finished.
            //
            std::shared_ptr<std::string> generate_error_string(const unsigned int errcode, std::string log_type, ...);             
            void print_err(std::string& message);
            void warn(unsigned int errcode, ...);
            void debug(unsigned int errcode, ...);

            [[noreturn]] void fatal(unsigned int errcode, ...);
        };
    };
};

#endif