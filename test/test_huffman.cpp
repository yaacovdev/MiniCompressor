#include <gtest/gtest.h>
#include "huffman.h"

// Test data structure initialization
TEST(HuffmanNodeTest, Initialization)
{
    HuffmanNode node('a', 5);
    EXPECT_EQ(node.character, 'a');
    EXPECT_EQ(node.frequency, 5);
    EXPECT_EQ(node.left, nullptr);
    EXPECT_EQ(node.right, nullptr);
}

// Test frequency table creation
TEST(HuffmanTest, CreateHuffmanNodes)
{
    Huffman huffman;
    std::string data = "aaabbc";
    huffman.buildFrequencyTable(data);

    auto nodes = huffman.createHuffmanNodes();
    std::unordered_map<char, int> expected = {{'a', 3}, {'b', 2}, {'c', 1}};
    EXPECT_EQ(nodes.size(), expected.size());
    for (HuffmanNode *node : nodes)
    {
        EXPECT_EQ(expected[node->character], node->frequency);
        delete node; // Free memory
    }
}
// Test creating Huffman nodes from an empty frequency table
TEST(HuffmanTest, CreateHuffmanNodesEmptyTable)
{
    Huffman huffman;
    auto nodes = huffman.createHuffmanNodes();
    EXPECT_TRUE(nodes.empty());
}

// Test creating Huffman nodes from a non-empty frequency table
TEST(HuffmanTest, CreateHuffmanNodesNonEmptyTable)
{
    Huffman huffman;
    huffman.buildFrequencyTable("aaabbc");
    auto nodes = huffman.createHuffmanNodes();
    EXPECT_EQ(nodes.size(), 3);

    std::unordered_map<char, int> expected = {{'a', 3}, {'b', 2}, {'c', 1}};
    for (HuffmanNode *node : nodes)
    {
        EXPECT_EQ(expected[node->character], node->frequency);
        delete node; // Free memory
    }
}

// Test building Huffman tree with non-empty frequency table
TEST(HuffmanTest, BuildHuffmanTreeNonEmptyTable)
{
    Huffman huffman;
    huffman.buildFrequencyTable("aaabbc");
    huffman.buildHuffmanTree();

    // Check root node
    HuffmanNode *root = huffman.getRoot();

    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->frequency, 6);

    huffman.printTree(root);

    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    EXPECT_EQ(root->left->frequency, 3);
    EXPECT_EQ(root->right->frequency, 3);
    EXPECT_EQ(root->left->character, 'a');

    // Check left subtree
    HuffmanNode *right = root->right;
    ASSERT_NE(right->left, nullptr);
    ASSERT_NE(right->right, nullptr);
    EXPECT_EQ(right->left->frequency, 1);
    EXPECT_EQ(right->left->character, 'c');
    EXPECT_EQ(right->right->frequency, 2);
    EXPECT_EQ(right->right->character, 'b');

    // Check right subtree
    HuffmanNode *left = root->left;
    EXPECT_EQ(left->frequency, 3);
    EXPECT_EQ(left->character, 'a');
}


// Test generating Huffman codes for a single character
TEST(HuffmanTest, GenerateCodesSingleCharacter)
{
    Huffman huffman;
    HuffmanNode node('a', 5);
    std::unordered_map<char, std::string> huffmanCodes;
    huffman.generateCodes(&node, "", huffmanCodes);
    EXPECT_EQ(huffmanCodes.size(), 1);
    EXPECT_EQ(huffmanCodes['a'], "");
}

// Test generating Huffman codes for multiple characters
TEST(HuffmanTest, GenerateCodesMultipleCharacters)
{
    Huffman huffman;
    huffman.buildFrequencyTable("aaabbc");
    huffman.buildHuffmanTree();

    std::unordered_map<char, std::string> huffmanCodes;
    huffman.generateCodes(huffman.getRoot(), "", huffmanCodes);

    EXPECT_EQ(huffmanCodes.size(), 3);
    EXPECT_EQ(huffmanCodes['a'], "0");
    EXPECT_EQ(huffmanCodes['b'], "11");
    EXPECT_EQ(huffmanCodes['c'], "10");
}

// Test generating Huffman codes for an empty tree
TEST(HuffmanTest, GenerateCodesEmptyTree)
{
    Huffman huffman;
    std::unordered_map<char, std::string> huffmanCodes;
    huffman.generateCodes(nullptr, "", huffmanCodes);
    EXPECT_TRUE(huffmanCodes.empty());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}