#ifndef JPEG_ENDIANNESS_TESTS_INCLUDE_LOGGING_LOG_HPP
#define JPEG_ENDIANNESS_TESTS_INCLUDE_LOGGING_LOG_HPP
namespace cnn_practice{
    namespace logging {
        class Log {

            private:
            //Log stream.
            bool echo_to_stderr;

            public:
            Log();
            Log(std::string filepath);

            void warn()
        };
    };
};
#endif