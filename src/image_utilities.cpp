#include <image_utilities.hpp>
namespace cnn_practice {
    namespace utilities {
        namespace image_utilities {
            bool is_jpeg_file(const std::shared_ptr<Config> config, const fs::path& file){
                std::string filename = convert_to_lowercase(file.filename()); 
                std::smatch match;
                std::regex matcher (
                    config -> filecheck_pattern,
                    std::regex::ECMAScript); //JavaScript syntax.
            
                bool retval = std::regex_search(
                    filename,
                    match,
                    matcher,
                    std::regex_constants::match_default
                );
                std::cerr << "Match ready: " << match.ready()
                          << " Match size: " << match.size()
                          << " Match empty: " << match.empty()
                          << "\n\n";
                return retval;
            }
        };
    };
};