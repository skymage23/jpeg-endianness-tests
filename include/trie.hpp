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

    //Methods:
    protected:
    TreeNode walk(const std::string&);

    private:
    int entry_count;

    public:
    CharStringTrie() : Tree(){ this -> entry_count = 0; };
    CharStringTrie(const std::string input);
    CharStringTrie(CharStringTrie&& old);

    void add(const std::string& new_input);
    bool contains(const std::string& str_to_check);
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

    std::vector<std::string> to_string();
};

    };
};
#endif