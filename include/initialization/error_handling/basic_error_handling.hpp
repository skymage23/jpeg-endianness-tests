#ifndef JPEG_ENDIANNESS_TESTS_INCLUDE_INITIALIZATION_ERROR_HANDLING_BASIC_ERROR_HANDLING
#define JPEG_ENDIANNESS_TESTS_INCLUDE_INITIALIZATION_ERROR_HANDLING_BASIC_ERROR_HANDLING

namespace cnn_practice {
    namespace initialization {
        namespace error_handling {
            const unsigned int errcode_min = 0;

            //If you add new errcodes, increment this value by
            //one for each errcode you add.
            const unsigned int errcode_max = 5;

            unsigned int success = 0;
            unsigned int out_of_memory = 1;
            unsigned int unrecognized_argument = 2;
            unsigned int too_few_arguments = 3;
            unsigned int too_many_arguments = 4;
            unsigned int file_write_error = 5;
            //int file_read_error = 6;

            std::string[] error_names = {
                //Hello:
                //success:
                "success",
                "out_of_memory",
                "unrecognized_argument",
                "too_few_arguments",
                "too_many_arguments",
                "file_write_error"
            };

            std::string generate_string__success();
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
            std::unique_ptr<std::string> generate_error_string(int errcode, std::string log_type, ...);             
            void print_err(std::string& message);
            void warn(int errcode, ...);
            void debug(int errcode, ...);
            void fatal(int errcode);
        };
    };
};

#endif