#include "huffman.h"
#include <string>
#include <iostream>
#include <queue>

/**
 * Builds a frequency table based on the given data.
 *
 * This function takes a string `data` as input and builds a frequency table
 * based on the characters in the string. The frequency table is stored in the
 * `frequencyTable` member variable of the `Huffman` class.
 *
 * @param data The input string to build the frequency table from.
 */
void Huffman::buildFrequencyTable(const std::string &data)
{
    for (char c : data)
    {
        frequencyTable[c]++;
    }
}

/**
 * Creates Huffman nodes based on the frequency table.
 * Each node represents a character and its frequency.
 *
 * @return A vector of pointers to HuffmanNode objects.
 */
std::vector<HuffmanNode *> Huffman::createHuffmanNodes()
{
    std::vector<HuffmanNode *> nodes;
    for (const auto &pair : frequencyTable)
    {
        nodes.push_back(new HuffmanNode(pair.first, pair.second));
    }
    return nodes;
}

/**
 * Builds the Huffman tree using the Huffman algorithm.
 * This function creates Huffman nodes, constructs a priority queue,
 * and merges nodes until a single root node is obtained.
 * The resulting root node represents the Huffman tree.
 */
void Huffman::buildHuffmanTree()
{
    auto nodes = createHuffmanNodes();
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, Compare> pq;

    for (auto node : nodes)
    {
        pq.push(node);
    }

    while (pq.size() > 1)
    {
        HuffmanNode *left = pq.top();
        pq.pop();
        HuffmanNode *right = pq.top();
        pq.pop();

        HuffmanNode *newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    root = pq.top();
}

/**
 * Prints the Huffman tree for debugging purposes.
 *
 * @param node The current node in the Huffman tree.
 * @param prefix The prefix string to indicate the level of the node.
 */
void Huffman::printTree(HuffmanNode *node, std::string prefix)
{
    if (!node)
        return;
    std::cout << prefix << (node->character ? node->character : '#') << ": " << node->frequency << std::endl;
    printTree(node->left, prefix + "L---");
    printTree(node->right, prefix + "R---");
}

/**
 * Generates Huffman codes for each character by traversing the Huffman tree.
 *
 * @param node The current node in the Huffman tree.
 * @param code The current Huffman code.
 * @param huffmanCodes A map to store the generated Huffman codes.
 */
void Huffman::generateCodes(HuffmanNode *node, const std::string &code, std::unordered_map<char, std::string> &huffmanCodes)
{
    if (!node)
        return;
    if (!node->left && !node->right)
    {
        huffmanCodes[node->character] = code;
    }
    generateCodes(node->left, code + "0", huffmanCodes);
    generateCodes(node->right, code + "1", huffmanCodes);
}

/**
 * Recursively deletes the Huffman tree.
 *
 * @param node The root node of the Huffman tree.
 */
void Huffman::deleteTree(HuffmanNode *node)
{
    if (!node)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}