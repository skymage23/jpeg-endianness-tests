#ifndef JPEG_ENDIANNESS_TESTS_INCLUDE_ERROR_HANDLING_ERRCODES_HPP
#define JPEG_ENDIANNESS_TESTS_INCLUDE_ERROR_HANDLING_ERRCODES_HPP

#include <unordered_map>
#include <memory>

namespace cnn_practice {
    namespace error_handling {
        struct ErrCodeRecord{
            unsigned long errcode;
            std::string name;
            std::string message;   
        }

        class ErrCodes {
            //Properties:
            private:
            long curr_available_code;
            bool write_enabled;

            std::unordered_map<unsigned_long, std::unique_ptr<ErrCodeRecord>> errcode_map;

            public:
            ErrCodes();
            ~ErrCodes();
            ErrCodes(ErrCodes&&) = delete;
            ErrCodes(ErrCodes&) = delete;

            //Disables adding new errcodes.
            //Re: avoid confusion.
            void disableWrite();

            //Generates errcode record and returns the generated errcode:
            unsigned long addErrCode(std::string name, std::string message);
        };

        std::shared_ptr<ErrCodes> errcode_singleton = std::shared_ptr<ErrCodes>(new ErrCodes());
    };
};
#endif