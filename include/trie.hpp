#ifndef CNN_PRACTICE_TRIE
#define CNN_PRACTICE_TRIE

//Includes:
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


#include <tree.hpp>

//Type definitions:
namespace cnn_practice {
    namespace collections {



class CharStringTrie : RootTreeNode {

    //Nested Classes:
    private:
     class TrieNode : DataStoreTreeNode<char>{
        private:
        bool is_leaf;

        TrieNode(
            char value,
            std::shared_ptr<TreeNode> parent,
            bool is_leaf
        ) : DataStoreTreeNode(value, parent){
            this -> is_leaf = is_leaf;
        }

    };

//    public:
//     class  

    //Properties:
    private:
    int edge_count;
    //std::shared_ptr<TrieNode> root;
    std::shared_ptr<
        std::vector<
            std::shared_ptr<TrieNode>
        >
    > root_children;

    //Methods:
    private:
    void insert(
        const std::string& input,
        std::string::const_iterator input_start,
        std::shared_ptr<TrieNode> node_start
    );

    public:
    CharStringTrie();
    CharStringTrie(const std::string input);
    CharStringTrie(CharStringTrie&& old);
    int get_edge_count();

    void add(const std::string& new_input);
    bool contains(const std::string& str_to_check);
    bool starts_with_value_in_trie(
        std::string::const_iterator begin,
        std::string::const_iterator end
    );

    bool starts_with_value_in_trie(
        std::string::reverse_iterator begin,
        std::string::reverse_iterator end
    );

    bool starts_with_value_in_trie(
        std::string::iterator begin,
        std::string::iterator end
    );

    std::vector<std::string> dump_entries();
};

    };
};
#endif