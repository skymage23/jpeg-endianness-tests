#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


#include <trie.hpp>
namespace fs = std::filesystem;

//Constants:
const std::string proj_dir_name = "jpeg-endianness-tests";
const std::string image_dir_name = "test_images";


//Type definitions:
typedef struct Config{
    cnn_practice::collections::CharStringTrie filetype_trie;
} Config;

std::string convert_to_lowercase(std::string input){
    std::transform(input.begin(), input.end(), input.begin(),
    [](unsigned char c){ return std::tolower(c); });
    
    return input;
}

std::shared_ptr<Config> get_config(){
    std::shared_ptr<Config> retval(new Config);
    //Makes searching trivial:
    retval -> filetype_trie.add(".gepj");
    retval -> filetype_trie.add(".gpj");
    return retval;
}


bool is_jpeg_file(const std::shared_ptr<Config> config, const fs::path& file){
    std::string filename = convert_to_lowercase(file.filename());
    return config -> filetype_trie.starts_with_value_in_trie(filename.rbegin(), filename.rend());
}

//This isn't working correctly.
//It fails when the CWD is already the project root.
std::shared_ptr<fs::path> get_project_dirtree_path(){
    //fs::path prev_path = fs::current_path();
    //fs::path path_check = prev_path.parent_path();
    fs::path path_check = fs::current_path();

    bool found = false;
    //When we are at the root_dir, current path and parent path
    //are the same.
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

std::vector<std::string> get_jpeg_image_paths(
    std::shared_ptr<Config> config,
    std::shared_ptr<fs::path> image_path
){
    fs::path p_temp;
    std::vector<std::string> retval;
    for(
        const fs::directory_entry dir_ent : 
        fs::recursive_directory_iterator(image_path -> string())
    ){   
        p_temp = dir_ent.path();
        if(is_jpeg_file(config, p_temp)){
            retval.push_back(p_temp.filename());
        }
    };

    return retval;
}

int main (){
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

    std::vector<std::string> images = get_jpeg_image_paths(config, image_path);
    
    std::cout << "******************************************\n";
    
    for(auto elem : images){
        std::cout << elem << "\n";
    }

    std::cout << "\n";
    return 0;
}
