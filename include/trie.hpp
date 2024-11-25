#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef CNN_PRACTICE_TRIE
#define CNN_PRACTICE_TRIE
namespace cnn_practice {
    namespace collections {


//Need some way to denote leaf nodes.
//
class CharStringTrie {

    //Nested Classes:
    private:
    struct TrieNode {
        char value;
        bool is_leaf;
        std::vector<std::shared_ptr<TrieNode*>> children;
    };

//    public:
//     class  

    //Properties:
    private:
    std::unique_ptr<TrieNode*> root;

    //Methods:
    private:
    void insert(
        const std::string& input,
        const std::string::iterator& input_start,
        std::shared_ptr<TrieNode*> node_start
    );

    public:
    CharStringTrie();
    CharStringTrie(const std::string input);
    CharStringTrie(CharStringTrie&& old);

    void add(const std::string new_input);
    void contains(const std::string str_to_check);

};

    };
};
#endif