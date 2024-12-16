#include <cstdarg>

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <cstdint>
#include <format>
#include <iostream>
#include <memory>
#include <string>

#include <initialization/error_handling/basic_error_handling.hpp>
namespace cnn_practice {
    namespace initialization {
        namespace error_handling {

            #ifndef NDEBUG
            const std::string variadic_print_prefix = "Variadic arg: %A\n";
            void print_variadic_arg_list(std::string prefix, ...){
                va_list args;
                va_start(args, prefix);
                vprintf(prefix.c_str(), args);
                va_end(args);
                return;
            }
            #endif

            std::string generate_string__success(){
                return "Success.";
            }

            std::string generate_string__invalid_errcode(unsigned int errcode){
                return std::format("Invalid errcode: {} ", errcode);
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
                return "Too many arguments.\n";
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

            //DO NOT CALL va_start.
            std::shared_ptr<std::string> generate_error_string(
                const unsigned int errcode,
                std::string log_type,
                va_list args
            ){
                std::string temp;
                #ifndef NDEBUG
                    print_variadic_arg_list("generate_error_string: " + variadic_print_prefix, args);
                #endif 
                
                if(errcode > ERRCODE_MAX){
                    return nullptr;
                }

                switch(errcode){
                    case SUCCESS: {
                        temp = generate_string__success();
                        break;
                    }
                    case INVALID_ERRCODE: {
                        unsigned int input = va_arg(args, unsigned int);
                        temp = generate_string__invalid_errcode(input);
                        break;
                    }
                    case OUT_OF_MEMORY: {
                        temp = generate_string__out_of_memory();
                        break;
                    }
                    case UNRECOGNIZED_ARGUMENT: {
                        //variadic:
                        std::string arg = va_arg(args, std::string);
                        temp = generate_string__unrecognized_argument(arg);
                        break;
                    }
                    case TOO_FEW_ARGUMENTS: {
                        temp = generate_string__too_few_arguments();
                        break;
                    }
                    case TOO_MANY_ARGUMENTS: {
                        temp = generate_string__too_many_arguments();
                        break;
                    }
                    case FILE_WRITE_ERROR: {
                        //variadic:
                        std::string filename = va_arg(args, std::string);
                        temp = generate_string__file_write_error(filename);
                        break;
                    }
                };
                temp = std::format("{}: {}", log_type, temp);
                return std::shared_ptr<std::string>(new std::string(temp));
            }

            std::shared_ptr<std::string> generate_error_string(
                const unsigned errcode,
                std::string log_type,
                ...
            ){
                va_list args;
                va_start(args, log_type);
                return generate_error_string(errcode, log_type, args);
            }        
            
            void print_err(std::shared_ptr<std::string> message){
                std::cerr << *message;
            }

            void fatal(const unsigned int errcode, ...) {
                va_list args;
                va_start(args, errcode);
                #ifndef NDEBUG
                    print_variadic_arg_list("fatal:  " + variadic_print_prefix, args);
                #endif
                std::shared_ptr<std::string> msg = generate_error_string(errcode, "FATAL", args);
                if(msg == nullptr){
                    //Problem.
                    msg = generate_error_string(INVALID_ERRCODE, "FATAL", errcode);
                }
                print_err(msg);
                exit(EXIT_FAILURE);
                va_end(args);
            }

            void warn(const unsigned int errcode, ...){
                va_list args;
                va_start(args, errcode);
                #ifndef NDEBUG
                    print_variadic_arg_list("warn:  " + variadic_print_prefix, args);
                #endif
                std::shared_ptr<std::string> msg = generate_error_string(errcode, "WARN", args);
                if (msg == nullptr){
                    fatal(INVALID_ERRCODE, errcode);                
                }
                print_err(msg);
            }

            void debug(const unsigned int errcode, ...) {
                va_list args;
                va_start(args, errcode);
                #ifndef NDEBUG
                    print_variadic_arg_list("debug:  " + variadic_print_prefix, args);
                #endif
                std::shared_ptr<std::string> msg = generate_error_string(errcode, "DEBUG", args);
                if (msg == nullptr){
                    fatal(INVALID_ERRCODE, errcode);                    
                }
                print_err(msg);
            }
        };
    };
};