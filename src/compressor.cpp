#include <iostream>
#include <fstream>
#include <string>
#include "compressor.h"
#include "huffman.h"

void compress(const std::string& file, const std::string& algorithm) {
    std::ifstream fp(file);
    if (!fp.is_open()) {
        std::cerr << "File not found" << std::endl;
        return;
    }

    std::cout << "Compressing file: " << file << std::endl;
    if (!algorithm.empty() && algorithm == "l") {
        std::cout << "Using LZW algorithm" << std::endl;
        // Appel à la fonction de compression LZW (à implémenter)
    } else {
        std::cout << "Using Huffman algorithm" << std::endl;
        // Huffman huffman;

        // std::string data((std::istreambuf_iterator<char>(fp)), std::istreambuf_iterator<char>());

        // huffman.buildHuffmanTree(data);
    }

    fp.close();
}
