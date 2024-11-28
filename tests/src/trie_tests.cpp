#include <cstdlib>
#include <future>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include <gtest/gtest.h>

#include <trie.hpp>

const std::string test_string = "pothead";
const std::string test_string_2 = "tweaker";
const std::string test_string_control = "goon";
bool infinite_loop_detected = false;

class TrieUnitTests : public ::testing::Test{
    protected:
    bool enable_skip = true;

    public:
    void SetUp(){
        char* env_check = getenv("DISABLE_GTEST_SKIP"); 
        enable_skip = (env_check == NULL);
    }
};

TEST(trie_tests, test_insert){
    cnn_practice::collections::CharStringTrie trie;
    trie.add(test_string);
    ASSERT_TRUE(trie.contains(test_string));
    ASSERT_FALSE(trie.contains(test_string_control));
    
}

TEST_F(TrieUnitTests, test_dump_no_inf_loop){
    bool result;
    cnn_practice::collections::CharStringTrie object;
    std::promise<std::vector<std::string>> promisedFinished;
    auto futureResult = promisedFinished.get_future();
    std::thread([](std::promise<std::vector<std::string>>& finished,
    cnn_practice::collections::CharStringTrie & obj) {
       std::vector<std::string> ret = obj.dump_entries();
       finished.set_value(ret);
    }, std::ref(promisedFinished), std::ref(object)).detach(); 

    result = (
        futureResult.wait_for(std::chrono::milliseconds(100))!= std::future_status::timeout
    );

    infinite_loop_detected = !result;
    EXPECT_TRUE(result);
}


TEST_F(TrieUnitTests, test_dump){
    if((this -> enable_skip) && infinite_loop_detected){
        GTEST_SKIP() << "Infinite loop was detected. This test is pointless until such is fixed.";
    }
    std::unordered_set<std::string> str_set;
    cnn_practice::collections::CharStringTrie trie;


    trie.add(test_string);
    str_set.insert(test_string);
    trie.add(test_string_2);
    str_set.insert(test_string_2);

    std::vector<std::string> trie_dump = trie.dump_entries();
//    ASSERT_EQ(trie_dump.size(), str_set.size());

    std::cout << "Trie dump: \n";
    for (auto elem : trie_dump){
        std::cout << elem << "\n";
        ASSERT_TRUE(str_set.contains(elem));
    }

}


TEST_F(TrieUnitTests, test_multistring_insert){
    cnn_practice::collections::CharStringTrie trie;
    int edge_count = 0;
    trie.add(test_string);
    trie.add(test_string_2);
    edge_count = trie.get_edge_count();
    ASSERT_EQ(edge_count, 14);
    ASSERT_TRUE(trie.contains(test_string));
    ASSERT_TRUE(trie.contains(test_string_2));
    ASSERT_FALSE(trie.contains(test_string_control));
}

