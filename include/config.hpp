#ifndef JPEG_ENDIANNESS_TESTS_INCLUDE_CONFIG_HPP
#define JPEG_ENDIANNESS_TESTS_INCLUDE_CONFIG_HPP

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include <initialization/config/initiralization_config.hpp>

namespace cnn_practice{
    namespace config {
        //Type definitions:
        class Config

        class Config {

            public:
            static std::shared_ptr<Config> parse_cli(
                InitializationConfig config,
                int argc,
                char*[] argv
            );
            private:
            //Config options needed in and inheritied from the initialization segment.
            cnn_practice::initialization::InitializationConfig init_config;

            std::string image_directory_path;
            bool have_display;
            bool disable_display;

            private:
            Config() = default;

            public:
            Config(config& input);
            Config(Config&& input);

            std::string get_image_directory_path();
            bool get_have_display();
            bool get_disable_display();


            std::string usage();
        };        
    };
};
#endif