#ifndef HUFFMAN_H
#define HUFFMAN_H

struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode *left, *right; 

     HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

#endif // HUFFMAN_H