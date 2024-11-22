#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

namespace fs = std::filesystem;

const std::string proj_dir = "jpeg-endianness-tests";

std::string get_project_dirtree_path(){
    fs::path path_check = fs::current_path();
    fs::path prev_path = path_check;
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
        return std::string();
    }

    return path_check.string();
}

int main (){
    std::string proj_path = get_project_dirtree_path();
    if (proj_path.empty()){
        std::cerr << "This program needs to be run from within the \"jpeg-endianness-tests\" directory.\n";
    }
    std::cout << proj_path << "\n";
}
