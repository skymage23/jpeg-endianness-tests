#ifndef JPEG_ENDIANNESS_TESTS_INCLUDE_INITIALIZATION_CONFIG_INITIALIZATION_CONFIG_HPP
#define JPEG_ENDIANNESS_TESTS_INCLUDE_INITIALIZATION_CONFIG_INITIALIZATION_CONFIG_HPP
#include <string>
#include <unordered_map>

namespace cnn_practice {
    namespace initialization {
        class InitializationConfig {

            private:
            bool log_echo_to_stderr;
            std::string log_file_location;

            private:
            InitializationConfig();

            public:
            InitializationConfig(InitializationConfig& input);
            InitializationConfig(InitializationConfig&& input);

            bool parse_cli(int arg, char* argv[]);

            std::string get_log_file_location();
            bool got_log_echo_to_stderr();

            std::string get_config_opts_usage_string();
        };
    };
};
#endif