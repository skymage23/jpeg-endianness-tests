#include <cstdlib>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include <opencv4/opencv2/opencv.hpp>


#include <config.hpp>
#include <image_utilities.hpp>
namespace cnn_practice {
    namespace config {

        Config::Config(){}


        std::shared_ptr<Config> get_config(int& errcode, int argc, char** args){
            
            std::shared_ptr<Config> retval(new Config);
            retval -> display = utilities::do_we_have_a_monitor();
            return retval;
        }
         
        
        static std::shared_ptr<std::filesystem::path> Config::compute_image_directory_path(
            std::shared_ptr<std::filesystem::path> proj_curr_path
        ){
            std::filesystem::path curr_path = (*proj_curr_path) / "test_images" ;
            std::filesystem::file_status f_status = std::filesystem::status(curr_path);
        
            if(f_status.type() == std::filesystem::file_type::not_found){
                return nullptr;
            }
        
            return std::shared_ptr<std::filesystem::path>(new std::filesystem::path(curr_path));
        }
        
        std::vector<cv::Mat> Config::get_unpacked_images(
            std::shared_ptr<Config> config,
            std::shared_ptr<std::filesystem::path> image_path
        ){
            std::filesystem::path p_temp;
            std::vector<std::filesystem::path> retval;
            for(
                const std::filesystem::directory_entry& dir_ent : 
                std::filesystem::recursive_directory_iterator(image_path -> string())
            ){   
                p_temp = dir_ent.path();
                if(is_jpeg_file(config, p_temp)){
                    retval.push_back(p_temp);
                }
            };
        
            return retval;
        }
    };
};