#include <cstdarg>
#include <cstdint>
#include <format>
#include <iostream>
#include <memory>
#include <string>

#include <initialization/error_handling/errcodes.hpp>
namespace cnn_practice {
    namespace initialization {
        namespace error_handling {
            std::string generate_string__success(){
                return "Success.";
            }
            
            std::string generate_string__out_of_memory(){
                return "Out of memory. Probably developer error,"
                       "but you can help this by seeing if there are any"
                       "running tasks/processes that are eating up large amounts"
                       "of memory and killing them.";
            }

            std::string generate_string__unrecognized_argument(
                std::string arg
            ){
                return "Unrecognized argument: " + arg;
            }
            
            std::string generate_string__too_many_arguments(){
                return "Too many arguments.\n",
            }
            
            std::string generate_string__too_few_arguments(){
                return "Too few arguments.\n";
            }
            
            std::string generate_string__file_write_error(
                std::string filename
            ){
                return "File write error: filename: " + filename;
            }

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
            std::unique_ptr<std::string> generate_error_string(int errcode, std::string log_type, ...){
                std::string temp;
                va_list args;
                
                if(errcode > errcode_max){
                    return nullptr;
                }

                case(errcode){
                    success:
                        temp = generate_string__success();
                        break;
                    out_of_memory:
                        temp = generate_string__out_of_memory();
                        break;
                    unrecognized_argument:
                        //variadic:
                        std::string arg = va_arg(args, std::string);
                        temp = generate_string__unrecognized_argument(arg);
                        break;
                    too_few_arguments:
                        temp = generate_string__too_few_arguments();
                        break;
                    too_many_arguments:
                        temp = generate_string__too_many_arguments();
                        break;
                    file_write_error:
                        //variadic:
                        std::string filename = va_arg(args, std::string);
                        temp = generate_string__file_write_error(filename);
                };
                temp = std::format("{}: {}", log_type, temp);
                return std::unique_ptr<std::string>(temp);
            }            
            
            void print_err(std::string& message){
                std::cerr << message;
            }

            void warn(int errcode, ...){
                print_err(generate_error_string("WARN", /*va_args*/ ));
            }

            void debug(int errcode, ...){
                print_err(generate_error_string("DEBUG:", /*va_args*/));
            }

            [[noreturn]] void fatal(int errcode) {
                print_err(generate_error_string("FATAL", /*va_args*/));
                exit(EXIT_FAILURE);    
            }
        };
    };
};