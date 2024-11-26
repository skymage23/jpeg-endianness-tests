#include <string>

#include <gtest/gtest.h>

#include <trie.hpp>

const std::string test_string = "pothead";
const std::string test_string_2 = "tweaker";
const std::string test_string_control = "goon";

TEST(trie_tests, test_insert){
    cnn_practice::collections::CharStringTrie trie;
    trie.add(test_string);
    ASSERT_TRUE(trie.contains(test_string));
    ASSERT_FALSE(trie.contains(test_string_control));
}

TEST(trie_tests, test_multistring_insert){
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

