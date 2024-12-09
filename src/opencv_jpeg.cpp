#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include <opencv4/opencv2/opencv.hpp>

namespace fs = std::filesystem;

//Constants:
const std::string proj_dir_name = "jpeg-endianness-tests";
const std::string image_dir_name = "test_images";


//Type definitions:
struct Config {
    std::string filecheck_pattern = R"(\.(?:jpeg|jpg)+$)";
};

std::string convert_to_lowercase(std::string input){
    std::transform(input.begin(), input.end(), input.begin(),
    [](unsigned char c){ return std::tolower(c); });    
    return input;
}

std::shared_ptr<Config> get_config(){
    std::shared_ptr<Config> retval(new Config);
    return retval;
}


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

std::shared_ptr<fs::path> get_project_dirtree_path(){
    fs::path path_check = fs::current_path();

    bool found = false;
    while (path_check != path_check.parent_path() && !found ){
	    if (path_check.filename() != proj_dir_name){
	        path_check = path_check.parent_path();
	        continue;
	    }
	    found = true;
    }

    if(!found){
        return nullptr;
    }
    //Move off of the stack and onto the heap:
    return std::shared_ptr<fs::path>(new fs::path(path_check));
}


std::shared_ptr<fs::path> get_image_directory_path(
    std::shared_ptr<fs::path> proj_curr_path
){
    fs::path curr_path = (*proj_curr_path) / "test_images" ;
    fs::file_status f_status = fs::status(curr_path);

    if(f_status.type() == fs::file_type::not_found){
        return nullptr;
    }

    return std::shared_ptr<fs::path>(new fs::path(curr_path));
}

std::vector<fs::path> get_jpeg_image_paths(
    std::shared_ptr<Config> config,
    std::shared_ptr<fs::path> image_path
){
    fs::path p_temp;
    std::vector<fs::path> retval;
    for(
        const fs::directory_entry& dir_ent : 
        fs::recursive_directory_iterator(image_path -> string())
    ){   
        p_temp = dir_ent.path();
        if(is_jpeg_file(config, p_temp)){
            retval.push_back(p_temp);
        }
    };

    return retval;
}

int main (){
    std::string temp;
    std::shared_ptr<Config> config = get_config(); 
    std::shared_ptr<fs::path> proj_path = get_project_dirtree_path();
    if (proj_path == nullptr){
        std::cerr << "This program needs to be run from within the \"jpeg-endianness-tests\" directory.\n";
        return 1;
    }

    
    std::shared_ptr<fs::path> image_path = get_image_directory_path(proj_path);

    if(image_path == nullptr){
        std::cerr << "The \"test_images\" directory does not exist.\n";
        return 1;
    }

    std::cout << image_path -> string() << "\n";

    std::vector<fs::path> images = get_jpeg_image_paths(config, image_path);
    
    std::cout << "******************************************\n";
    
    for(auto elem : images){
        temp = elem.generic_string();
        std::cout << temp << "\n";
        cv::Mat image = cv::imread(temp);
        cv::namedWindow(temp, cv::WINDOW_NORMAL);
        cv::imshow(temp, image);
        cv::resizeWindow(temp, 800, 600); //VGA
        cv::waitKey(0);
    }

    std::cout << "\n";
    return 0;
}
