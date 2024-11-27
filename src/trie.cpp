#include <memory>
#include <stack>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>


#include <collections.hpp>
#include <trie.hpp>
#include <__trie.hpp>

CN_COLL_NS(CharStringTrie::CharStringTrie)(){
    this -> edge_count = 0;
    this -> root = std::shared_ptr<
        cnn_practice::collections::CharStringTrie::TrieNode
    >(new TrieNode());
    this -> root -> value = '\0';
}

CN_COLL_NS(CharStringTrie::CharStringTrie)(std::string input) : CharStringTrie(){
   this -> add(input);
}

CN_COLL_NS(CharStringTrie::CharStringTrie)(CN_COLL_NS(CharStringTrie&&) old){
    this -> root = std::move(old.root);
}

int CHAR_TRIE_MEMBER(get_edge_count)(){
    return this -> edge_count;
}

void CHAR_TRIE_MEMBER(insert)(
    const std::string& input,
    std::string::const_iterator input_start,
    std::shared_ptr<TrieNode> node_start    
){
   //Write insertion logic here.
   std::shared_ptr<TrieNode> curr_node, ptr_temp;
   curr_node = node_start;

   for(; input_start != input.end(); input_start++){
       ptr_temp = std::shared_ptr<TrieNode>(new TrieNode);
       ptr_temp -> value = *input_start;
       curr_node -> children.push_back(ptr_temp);
       this -> edge_count = this -> edge_count + 1;
       curr_node = ptr_temp;
   }
   curr_node -> is_leaf = true;
}

void CHAR_TRIE_MEMBER(add)(const std::string& input){
    bool found = false;
    bool insert = true;
    //bool break_outer = false;
    if (input.empty()){
        return;
    }

    std::shared_ptr<TrieNode> curr_node = this -> root;
    std::shared_ptr<TrieNode> insert_node_start;
    std::string::const_iterator iter = input.begin();
    std::string::const_iterator input_end = input.end();

    for(; iter != input_end; iter++){

        for(auto ptr : curr_node -> children){
            if (ptr -> value == *iter){
                found = true;
                curr_node = ptr;
                break;
            }
        }

        if(!found){
            insert = true;
            insert_node_start = curr_node;
            break;
        }

        //Ok. What happens if the string does
        //exist in the trie, but as a substring
        //of a larger string?
        if ((iter + 1) == input_end){
            if(!curr_node -> is_leaf){
                insert = true;
                insert_node_start = this -> root;
                iter = input.begin();
            }
        }
        found = false;
    } //end outer for.

    if (insert){
        this -> insert(input, iter, insert_node_start);
    }
 }

 bool CHAR_TRIE_MEMBER(contains)(
    const std::string& input
 ){
    return this -> starts_with_value_in_trie(input.begin(), input.end()); 
 }

 bool CHAR_TRIE_MEMBER(starts_with_value_in_trie)(
    std::string::const_iterator begin,
    std::string::const_iterator end
 ) {
    bool found = false;
    //Hello:
    std::shared_ptr<TrieNode> curr_node = this -> root;
    for(; begin != end; begin++){
        for(auto node : curr_node -> children){
            if(node -> value == *begin){
                found = true;
                curr_node = node;
            }
        }
        if(!found){
            return false;
        }
    }

    //Remember. We don't care about substrings. 
    return curr_node -> is_leaf;
 }


 bool CHAR_TRIE_MEMBER(starts_with_value_in_trie)(
    std::string::reverse_iterator begin,
    std::string::reverse_iterator end
 ) {
    bool found = false;
    //Hello:
    std::shared_ptr<TrieNode> curr_node = this -> root;
    for(; begin != end; begin++){
        for(auto node : curr_node -> children){
            if(node -> value == *begin){
                found = true;
                curr_node = node;
            }
        }
        if(!found){
            return false;
        }
    }

    //Remember. We don't care about substrings. 
    return curr_node -> is_leaf;
 }


 bool CHAR_TRIE_MEMBER(starts_with_value_in_trie)(
    std::string::iterator begin,
    std::string::iterator end
 ) {
    bool found = false;
    //Hello:
    std::shared_ptr<TrieNode> curr_node = this -> root;
    for(; begin != end; begin++){
        for(auto node : curr_node -> children){
            if(node -> value == *begin){
                found = true;
                curr_node = node;
            }
        }
        if(!found){
            return false;
        }
    }

    //Remember. We don't care about substrings. 
    return curr_node -> is_leaf;
 }


 std::vector<std::string> CHAR_TRIE_MEMBER(dump_entries)(){
    //Data structures:
    typedef struct StackNode {
        unsigned long curr_child_ind = 0;
        std::shared_ptr<TrieNode> trie_node;
        
    } StackNode;

     //Hello.
    std::vector<std::string> retval;
    std::vector<std::shared_ptr<StackNode>> node_stack;;
    std::shared_ptr<StackNode> stack_elem;

    //Gets allocated when are ready to walk the stack back.
    char* char_arr_temp = NULL;
    size_t char_stack_size = 0;

    //Depth first: 
    node_stack.push_back(std::shared_ptr<StackNode>(new StackNode{0, this -> root}));

    while(!node_stack.empty()){
        stack_elem = node_stack[node_stack.size() - 1];
        if(stack_elem -> trie_node -> is_leaf){
            //Add complete string to retval.
            //Now that we have found the leaf node,
            //pop from the stack until it is empty.
            //Then, if the, at the time, value of node_temp
            //has another child, place said child on the stack.
            char_stack_size = node_stack.size();
            char_arr_temp = new char[char_stack_size];
            for (unsigned long i = char_stack_size - 1; i != 0; i--){
                 char_arr_temp[i] = node_stack[i] -> trie_node -> value;
            }
            retval.push_back(std::string(char_arr_temp));
            delete[] char_arr_temp;
        }

        if(stack_elem -> curr_child_ind < stack_elem -> trie_node -> children.size()){
            node_stack.push_back(
                std::shared_ptr<StackNode>(
                    new StackNode{
                        0,
                        stack_elem -> trie_node -> children[stack_elem -> curr_child_ind]
                    }
                )
            );
            stack_elem -> curr_child_ind += 1;
        } else {
            node_stack.pop_back();
        }
    }
    return retval;
 }