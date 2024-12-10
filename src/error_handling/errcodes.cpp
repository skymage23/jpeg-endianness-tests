#include <unordered_map>
#include <string>

#include <error_handling/errcodes.hpp>

namespace cnn_practice {
    namespace error_handling {
        ErrCodes::ErrCodes() : curr_available_code(0),
        write_enabled(true),
        errcode_map(std::unordered_map<std:::string, ErrCodeRecord>())
        {}

        unsigned long addErrCode(std::string name, std::string message){
            if (this -> disableWrite){

            }
            unsigned long errcode = this -> curr_available_code;
            this -> curr_available_code += 1;
            this -> errcode_map.insert({errcode, name, message});
            return errcode;
        } 
    };
};