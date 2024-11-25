#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

const std::string proj_dir_name = "jpeg-endianness-tests";
const std::string image_dir_name = "test_images";

typedef struct TrieNode {
    const char value;
    int num_children;
} TrieNode;

//Not trying to be clever.
//This is just the most straightforward
//way for me to check file types without using
//regexes.
const int jpeg_ft_trie_size = 5;
const TrieNode jpeg_file_type_trie[jpeg_ft_trie_size] = {
    TrieNode{'\0', 2},
    TrieNode{'g', 1},
    TrieNode{'G', 2}
    TrieNode{'p', 2},
    TrieNode{'j', 0},
    TrieNode{'e', 1},
    TrieNode{'j', 0}
};

bool is_jpeg_file(const fs::path& file){
    std::vector<int> trie_index_stack;
    std::string temp;
    TrieNode node_temp;
    fs::file_status f_status = fs::status(file);
    if(f_status.type() != fs::file_type::regular){
        return false;
    }

    //Is JPEG?
    temp = file.string();
    std::string::reverse_iterator riter = temp.rbegin();

    //Walk the trie:
    for(int i = 0; i < jpeg_ft_trie_size;){
        node_temp = jpeg_file_type_trie[i];
        if (*riter == *(node_temp.value)){
           i = i + (node_temp.num_children - 1); 
           riter++;
        } else if (trie_index_stack.size() > 0) { 
            //Skip to next child:
        } else {
           return false;
        }
    }

    return true;
}

std::shared_ptr<fs::path> get_project_dirtree_path(){
    fs::path prev_path = fs::current_path();
    fs::path path_check = prev_path.parent_path();
    bool found = false;
    while ( path_check != prev_path && !found ){
	    if (path_check.filename() != proj_dir_name){
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
    std::string str_temp;
    std::vector<std::string> retval;
    for(const fs::directory_entry dir_ent : 
        fs::recursive_directory_iterator(image_path -> string())){   
        str_temp = dir_ent.path().string();
        if(str_temp ){

        }
    };

    return retval;
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
