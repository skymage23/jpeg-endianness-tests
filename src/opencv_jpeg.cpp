#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

const std::string proj_dir = "jpeg-endianness-tests";

std::shared_ptr<fs::path> get_project_dirtree_path(){
    fs::path prev_path = fs::current_path();
    fs::path path_check = prev_path.parent_path();
    bool found = false;
    while ( path_check != prev_path && !found ){
	    if (path_check.filename() != proj_dir){
            prev_path = path_check;
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
    std::shared_ptr<fs::path> image_path
){
    for(const fs::directory_entry dir_ent : 
        fs::recursive_directory_iterator(image_path -> string())){
    
    }
}

int main (){
    std::shared_ptr<fs::path> proj_path = get_project_dirtree_path();
    if (proj_path == nullptr){
        std::cerr << "This program needs to be run from within the \"jpeg-endianness-tests\" directory.\n";
    }
    
    std::shared_ptr<fs::path> image_path = get_image_directory_path(proj_path);
    if(image_path == nullptr){
        std::cerr << "The \"test_images\" directory does not exist.\n";
    }

    std::cout << image_path -> string() << "\n";
    return 0;
}
