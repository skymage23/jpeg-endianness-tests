#include <utility>

#include <trie.hpp>
#define cn_coll_ns(a) cnn_practice::collections::a

cn_coll_ns(CharStringTrie)(){
    this -> root = new TrieNode();
    this -> root -> value = '\0';
}

cn_coll_ns(CharStringTrie)(std::string input) : CharStringTrie(){
   this -> add(input);
}

cn_coll_ns(CharStringTrie)(cn_coll_ns(CharStringTrie&&) old){
    this -> root = std::move(old -> root);
}

void cn_coll_ns(CharStringTrie::insert)(
    const std::string& input
    const std::string::iterator& input_start,
    std::shared_ptr<TrieNode*> node_start    
){
   //Write insertion logic here. 
}

void cn_coll_ns(CharStringTrie::add)(const std::string& input){
    bool found = false;
    bool insert = true;
    //bool break_outer = false;
    if (input.empty()){
        return;
    }

    std::shared_ptr<TrieNode*> curr_node = this -> root;
    std::shared_ptr<TrieNode*> insert_node_start;
    std::string::iterator iter = input.begin();

    for(; iter != input.end(); iter++){

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
            insert_iter_start = iter;
            break;
        }

        //Ok. What happens if the string does
        //exist in the trie, but as a substring
        //of a larger string?
        if ((iter + 1) == input.end()){
            if(!curr_node.is_leaf){
                insert = true;
                insert_node_start = this -> root;
                insert_iter_start = input.begin();
            }
        }
        found = false;
    } //end outer for.

    if (insert){
        this -> insert(&input, &iter, insert_node_start);
    }
 }

 bool cn_coll_ns(CharStringTrie::contains)(){

 }