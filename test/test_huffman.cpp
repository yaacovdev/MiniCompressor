#include <gtest/gtest.h>
#include "huffman.h"

// Test data structure initialization
TEST(HuffmanNodeTest, Initialization) {
    HuffmanNode node('a', 5);
    EXPECT_EQ(node.character, 'a');
    EXPECT_EQ(node.frequency, 5);
    EXPECT_EQ(node.left, nullptr);
    EXPECT_EQ(node.right, nullptr);
}

// Ajoutez plus de tests ici pour couvrir toutes les fonctionnalités de Huffman

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
