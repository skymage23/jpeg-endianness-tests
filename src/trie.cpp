#include <memory>
#include <stack>
#include <stdlib.h>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

#include <tree.hpp>
#include <trie.hpp>

namespace cnn_practice {
namespace collections {

void CharStringTrie::insert(
    const std::string& input,
    std::string::const_iterator input_start,
    std::shared_ptr<DataStoreTreeNode<char>> node_start    
){
   //Write insertion logic here.
   std::shared_ptr<DataStoreTreeNode<char>> curr_node, ptr_temp;
   curr_node = node_start;

   for(; input_start > input.end() - 1; input_start++){
       ptr_temp = std::shared_ptr<DataStoreTreeNode<char>>(
           new DataStoreTreeNode<char>(false, *input_start, curr_node)
       );
       curr_node -> addChild(std::static_pointer_cast<TreeNode>(ptr_temp));
       curr_node = ptr_temp;
   }
   ptr_temp = std::shared_ptr<DataStoreTreeNode<char>>(
       new DataStoreTreeNode<char>(true, *input_start, curr_node)
   );
   curr_node -> addChild(std::static_pointer_cast<TreeNode>(ptr_temp));
}

CharStringTrie::WalkResult CharStringTrie::trie_walk(
    const std::string& input,
    bool allow_prefix_match
){
    bool continue_outer = false;
    unsigned long char_match_count = 0;
    if (input.empty()){
        return WalkResult(0, nullptr);
    }

    std::shared_ptr<TreeNode> curr_node = std::static_pointer_cast<TreeNode>(this -> root);
    std::string::const_iterator iter = input.begin();
    std::string::const_iterator input_end = input.end();

    for(; (iter != input_end) && continue_outer; iter++){
        continue_outer = false;
        for(std::shared_ptr<collections::TreeNode> ptr : *(curr_node -> children)){
            if (
                (
                    std::static_pointer_cast<DataStoreTreeNode<char>>(ptr)
                ) -> getValue() == *iter
            ){
               curr_node = ptr;
               char_match_count++;
               continue_outer = true;
               break;
            }
        }
    } //end outer for.
    if (!allow_prefix_match && char_match_count != input.size()){
        return WalkResult(0, nullptr);
    }

    return WalkResult(char_match_count, curr_node);
}

std::shared_ptr<TreeNode> CharStringTrie::walk(
    const std::string &input
){
    return (this -> trie_walk(input, false)).get_end_tree_node();
}

void CharStringTrie::add (const std::string& input){
    unsigned counter = 0;

    CharStringTrie::WalkResult walk_result = this -> trie_walk(input, true);
    std::shared_ptr<collections::TreeNode> curr_node = walk_result.get_end_tree_node();
    std::shared_ptr<collections::TreeNode> new_node = nullptr;
    if(walk_result.get_char_match_count() == input.size()){
        return;
    }

    for(counter = walk_result.get_char_match_count();
        counter < input.size() - 1; counter++
    ){
        new_node = std::shared_ptr<DataStoreTreeNode<char>>(
            new DataStoreTreeNode<char>(
                false,
                input[counter],
                std::static_pointer_cast<DataStoreTreeNode<char>>(curr_node)
            )
        );
        curr_node -> addChild(new_node);
        curr_node = new_node;
    }
    new_node = std::shared_ptr<DataStoreTreeNode<char>>(
        new DataStoreTreeNode<char>(
            true,
            input[counter],
            std::static_pointer_cast<DataStoreTreeNode<char>>(curr_node)
        )
    );
    curr_node -> addChild(new_node);
    this -> entry_count += 1;
 }


 std::vector<std::string> CharStringTrie::to_string(){

    std::vector<std::string> retval;
    char* char_buff = NULL;
    int tree_level = 0;
    unsigned long long_temp = 0;
    std::shared_ptr<DataStoreTreeNode<char>> curr_node, node_temp, child_node;
    std::vector<std::shared_ptr<DataStoreTreeNode<char>>> stack;

    //Begin:
    stack.push_back(this -> root);
    tree_level = 1;

    while(!stack.empty()){
        //curr_node = stack[stack.size() - 1];
        curr_node = stack[stack.size() - 1];
        stack.pop_back();

        for(unsigned long i  = 0; i < curr_node -> children -> size(); i++){
            child_node = std::static_pointer_cast<DataStoreTreeNode<char>>((*(curr_node -> children))[i]);
            if (child_node -> is_leaf()){
                char_buff = static_cast<char*>(new char[tree_level]);
                node_temp = child_node;
                for (long_temp = tree_level - 1; long_temp > 0; long_temp--){
                    char_buff[long_temp] = node_temp -> getValue();
                    node_temp = std::static_pointer_cast<DataStoreTreeNode<char>>(node_temp -> parent);
                }
                char_buff[0] = node_temp -> getValue();
                retval.push_back(std::string(char_buff));
                delete[] char_buff;
            }
            stack.push_back(child_node);
            tree_level++;
        }
    } 
    return retval;
 }
};
};