#ifndef JPEG_ENDIANNESS_TESTS_INCLUDE_IMAGE_UTILITIES_HPP
#define JPEG_ENDIANNESS_TESTS_INCLUDE_IMAGE_UTILITIES_HPP

#include <filesystem>
#include <memory>

namespace cnn_practice {
    namespace utilities {
        namespace image_utilities {
            
            //We don't need to do so right now but this could be generated
            //by a compile-time script.
            const std::string filecheck_pattern = R"(\.(?:jpeg|jpg)+$)";

            //Uses a regex to check if the file in question is a JPEG file.
            //Returns: "true", if it is. Else, returns "false".
            bool is_jpeg_file(const std::shared_ptr<Config> config, const std::fileystem::path& file);
        };
    };
};
#endif