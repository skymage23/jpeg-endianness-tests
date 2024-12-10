#ifndef JPEG_ENDIANNESS_TESTS_INCLUDE_UTILITIES_HPP
#define JPEG_ENDIANNESS_TESTS_INCLUDE_UTILITIES_HPP
namespace cnn_practice {
    namespace utilities {
        std::string convert_to_lowercase(std::string input);
        bool do_we_have_a_monitor();
        std::vector<fs::path> get_jpeg_image_paths(
            std::shared_ptr<Config> config,
            std::shared_ptr<fs::path> image_path
        );
        bool is_jpeg_file(const std::shared_ptr<Config> config, const fs::path& file);
    };
};
#endif