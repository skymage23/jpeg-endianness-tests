#include <memory>
#include <stack>
#include <stdlib.h>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>


#include <collections.hpp>
#include <memory/memory.hpp>
#include <tree.hpp>
#include <trie.hpp>
#include <__trie.hpp>


/*void CHAR_TRIE_MEMBER(insert)(
    const std::string& input,
    std::string::const_iterator input_start,
    std::shared_ptr<CN_COLL_NS(DataStoreTreeNode<char>)> node_start    
){
   //Write insertion logic here.
   std::shared_ptr<CN_COLL_NS(DataStoreTreeNode<char>)> curr_node, ptr_temp;
   curr_node = node_start;

   for(; input_start > input.end() + 1; input_start++){
       ptr_temp = std::shared_ptr<CN_COLL_NS(DataStoreTreeNode<char>)>(
           new CN_COLL_NS(DataStoreTreeNode<char>)(false, *input_start, curr_node)
       );
       curr_node -> addChild(ptr_temp);
       curr_node = ptr_temp;
   }
   ptr_temp = new std::shared_ptr<CN_COLL_NS(TreeNode)>(
       new DataStoreTreeNode<char>(true, *input_start, curr_node)
   );
   curr_node -> addChild(true);
}
*/
CHAR_TRIE_MEMBER(__WalkResult) CHAR_TRIE_MEMBER(__walk)(
    const std::string& input,
    bool allow_prefix_match
){
    bool continue_outer = true;
    unsigned long char_match_count = 0;
    if (input.empty()){
        return __WalkResult(0, nullptr);
    }

    //A hack so that we can wrap "this" in a shared_ptr
    //without the object being deleted when the smart 
    //pointer is destroyed.
    std::shared_ptr<
        CN_COLL_NS(TreeNode)
    > curr_node (
        std::dynamic_cast<CN_COLL_NS(TreeNode)*>(this),
        cnn_practice::memory::EmptyDeleter<CN_COLL_NS(TreeNode)*>()
    );

    std::string::const_iterator iter = input.begin();
    std::string::const_iterator input_end = input.end();

    for(; iter != input_end; iter++){
        for(auto ptr : *(curr_node -> children)){
            if (
                std::dynamic_cast<
                    CN_COLL_NS(DataStoreTreeNode<char>)
                >(*ptr) -> value == *iter
            ){
                curr_node = ptr;
                continue_outer = true;
                char_match_count++;
                break;
            }
        }
        if (!continue_outer){
            break;
        }
    } //end outer for.
    if (!allow_prefix_match && char_match_count != input.size()){
        return __WalkResult(0, nullptr);
    }

    return __WalkResult(char_match_count, curr_node);
}

CN_COLL_NS(TreeNode) CHAR_TRIE_MEMBER(walk)(
    const std::string &input
){
    return (this -> __walk(input, false)).get_end_tree_node();
}

void CHAR_TRIE_MEMBER(add)(const std::string& input){
    unsigned counter = 0;

    __WalkResult walk_result = this -> __walk(input, true);
    std::shared_ptr<CN_COLL_NS(TreeNode)> curr_node = walk_result.get_end_tree_node();
    std::shared_ptr<CN_COLL_NS(TreeNode)> new_node = nullptr;
    if(walk_result.get_char_match_count() == input.size()){
        return;
    }

    for(counter = walk_result.get_char_match_count() - 1;
        counter < input.size() - 1; i++
    ){
        new_node = std::shared_ptr<DataStoreTreeNode<char>>(
            new DataStoreTreeNode(false, input[i], curr_node)
        );
        curr_node -> addChild(new_node);
        curr_node = new_node;
    }
    new_node = std::shared_ptr<DataStoreTreeNode<char>>(
        DataStoreTreeNode(true, input[counter], curr_node)
    );
    curr_node -> addChild(new_node);
 }




 std::vector<std::string> CHAR_TRIE_MEMBER(to_string)(){

    //Helper classes:
    /*struct StackEntry {
        unsigned long index;
        std::shared_ptr<CN_COLL_NS(TreeNode)> node;

        StackEntry(){
            index = 0;
            node = nullptr;
        }

        StackEntry(
            unsigned long index,
            std::shared_ptr<CN_COLL_NS(TreeNode)> node
        ) : index(index), node(node){}

        StackEntry(StackEntry&& input){
            this -> index = input.index;
            this -> node = input.node;
        }
    }*/
    
    std::vector<std::string> retval;
    char* char_buff = NULL;
    int tree_level = 0;
    unsigned long long_temp = 0;
    //StackEntry curr_node;
    std::shared_ptr<std::vector<std::shared_ptr<CN_COLL_NS(TreeNode)>>> curr_vec = nullptr;
    //std::vector<StackEntry> stack;
    std::vector<std::shared_ptr<CN_COLL_NS(TreeNode)>> stack;
    std::shared_ptr<DataStoreTreeNode<char>> node_temp;

    //Begin:
    /*stack.push_back(
        StackEntry(
            0,
            std::shared_ptr<CN_COLL_NS(TreeNode)>(this, memory::EmptyDeleter())
        )
    );*/

    stack.push_back(this -> children);
    tree_level = 1;

    while(!stack.empty()){
        //curr_node = stack[stack.size() - 1];
        curr_vec = stack[stack.size() - 1];
        stack.pop_back();

        for(auto ptr : curr_vec){
            if (!(ptr -> is_leaf())){
                char_buff = new char[tree_level];
                node_temp = std::static_cast<
                    std::shared_ptr<CN_COLL_NS(DataStoreTreeNode<char>)>
                >(ptr);
                for (long_temp = tree_level - 1; long_temp != 0; long_temp--){
                    char_buff[i] = node_temp -> value;
                    node_temp = std::static_cast<
                        std::shared_ptr<CN_COLL_NS(DataStoreTreeNode<char>)>
                    >(node_temp -> parent);
                }
                char_buff[0] = node_temp -> value;
                retval.push_back(std::string(char_buff));
                delete char_buff;
            }
            stack.push_back(ptr -> children);
            tree_level++;
        }
    } 
    return retval;
 }