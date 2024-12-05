#ifndef CNN_PRACTICE_TRIE
#define CNN_PRACTICE_TRIE

//Includes:
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <tree.hpp>

using cnn_practice::collections::TreeNode;

//Type definitions:
namespace cnn_practice {
    namespace collections {

class CharStringTrie : public Tree<std::string, char> {

    private:
    //Private classes:
    class WalkResult{
        private:
        unsigned long char_match_count;
        std::shared_ptr<TreeNode> end_tree_node;

        //Methods:
        public:
        WalkResult(int char_match, const std::shared_ptr<TreeNode> end_node) :
            char_match_count(char_match), end_tree_node(end_node){}

        unsigned long get_char_match_count() { return this -> char_match_count; }
        std::shared_ptr<TreeNode> get_end_tree_node() { return this -> end_tree_node;}
    };

    private:
    int entry_count;

    //Methods:
    protected:
    WalkResult trie_walk(const std::string& input, bool allow_prefix_match);
    std::shared_ptr<TreeNode> walk(const std::string&);

    void insert(
        const std::string& input,
        std::string::const_iterator input_start,
        std::shared_ptr<DataStoreTreeNode<char>> node_start    
    );

    public:
    CharStringTrie() : Tree(),entry_count(0){};
    CharStringTrie(const std::string& input) : Tree(input), entry_count(1){}
    CharStringTrie(CharStringTrie&& old) : 
        Tree(static_cast<Tree&&>(old))
    {
        this -> root = old.root;
    }

    void add(const std::string& new_input);
/*    bool contains(const std::string& str_to_check);
    bool contains(
        std::string::const_iterator begin,
        std::string::const_iterator end
    );

    bool contains(
        std::string::reverse_iterator begin,
        std::string::reverse_iterator end
    );

    bool contains(
        std::string::iterator begin,
        std::string::iterator end
    );

    int get_entry_count() { return this -> entry_count };
*/
    std::vector<std::string> to_string();
    int get_entry_count(){ return this -> entry_count; }
};

    };
};
#endif