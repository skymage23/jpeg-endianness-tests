#ifndef JPEG_ENDIANNESS_TESTS_INCLUDE_CONFIG_HPP
#define JPEG_ENDIANNESS_TESTS_INCLUDE_CONFIG_HPP

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include <opencv4/opencv2/opencv.hpp>

namespace cnn_practice{
    namespace config {
        //Type definitions:
        class Config {

            private:
            static std::filesystem::path compute_image_directory_path(
                std::filesystem::path> proj_curr_path
            );

            public:

            static std::shared_ptr<Config> get_config();

            private: 
            std::string image_directory_path;
            bool display;

            private:
            Config() = default;

            public:
            Config(config& input);
            Config(Config&& input);

            bool have_display();
            std::string get_image_directory_path();
            std::vector<cv::Mat> get_unpacked_images();
        };

        
    };
};
#endif