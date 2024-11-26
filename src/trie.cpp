#include <memory>
#include <string>
#include <utility>


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
    //Hello.
    std::vector<std::string> retval;
    std::vector<std::shared_ptr<TrieNode>> node_stack;

    //Depth first: 
    node_stack.push_back(this -> root);
    while(node_stack.size() > 0){
        while
    }

 }