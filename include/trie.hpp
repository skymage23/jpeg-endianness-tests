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

class CharStringTrie : Tree<std::string> {

    private:
    //Private classes:
    class __WalkResult{
        private:
        unsigned long char_match_count;
        std::shared_ptr<TreeNode> end_tree_node;

        //Methods:
        public:
        __WalkResult(int char_match, std::shared_ptr<TreeNode> end_node) :
            char_match_count(char_match), end_tree_node(end_node){}

        int get_char_match_count() { return this -> char_match_count; }
        std::shared_ptr<TreeNode> get_end_tree_node { return this -> end_tree_node;}
    }

    private:
    int entry_count;


    //Methods:
    protected:

    __WalkResult __walk(const T& input, bool allow_prefix_match);
    std::shared_ptr<CN_COLL_NS(TreeNode)> walk(const std::string&);
    void insert(
        const std::string& input,
        std::string::const_iterator input_start,
        std::shared_ptr<CN_COLL_NS(TreeNode)> node_start    
    );

    public:
    CharStringTrie() : Tree(){};
    CharStringTrie(const std::string input) : Tree(input){};
    CharStringTrie(CharStringTrie&& old);

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
};

    };
};
#endif