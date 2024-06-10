#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <unordered_map>
#include <vector>
#include <string>

struct HuffmanNode
{
    char character;
    int frequency;
    struct HuffmanNode *left, *right;

    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

struct Compare
{
    bool operator()(HuffmanNode *a, HuffmanNode *b)
    {
        return a->frequency > b->frequency;
    }
};

class Huffman
{
public:
    Huffman() {}
    ~Huffman() { deleteTree(root); }

    void buildFrequencyTable(const std::string &data);
    std::vector<HuffmanNode *> createHuffmanNodes();

    // Getter for frequency table for testing
    std::unordered_map<char, int> getFrequencyTable() const { return frequencyTable; }

    void buildHuffmanTree();
    HuffmanNode *getRoot() const { return root; }

    void generateCodes(HuffmanNode *node, const std::string &prefix, std::unordered_map<char, std::string> &codes);


private:
    void printTree(HuffmanNode *node, std::string prefix = "");


    void deleteTree(HuffmanNode *node);

    std::unordered_map<char, int> frequencyTable;
    HuffmanNode *root = nullptr;

    friend class HuffmanTest_BuildHuffmanTreeNonEmptyTable_Test;
};

#endif // HUFFMAN_H