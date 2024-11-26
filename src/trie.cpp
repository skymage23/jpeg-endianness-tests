#include <memory>
#include <string>
#include <utility>


#include <collections.hpp>
#include <trie.hpp>
#include <__trie.hpp>

CN_COLL_NS(CharStringTrie::CharStringTrie)(){
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

void CHAR_TRIE_MEMBER(insert)(
    const std::string& input,
    std::string::const_iterator input_start,
    std::shared_ptr<TrieNode> node_start    
){
   //Write insertion logic here.
   std::shared_ptr<TrieNode> curr_node, ptr_temp;
   curr_node = node_start;

   for(; input_start != input.end(); input_start++){
       ptr_temp = std::shared_ptr<TrieNode>(new TrieNode());
       ptr_temp -> value = *input_start;
       curr_node -> children.push_back(ptr_temp);
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
    bool found = false;
    //Hello:
    std::shared_ptr<TrieNode> curr_node = this -> root;
    for(auto iter = input.begin(); iter != input.end(); iter++){
        for(auto node : curr_node -> children){
            if(node -> value == *iter){
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