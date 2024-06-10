#include <iostream>
#include <fstream>
#include <string>
#include "compressor.h"
#include "huffman.h"
#include <cstdint>

void compress(const std::string &file, const std::string &algorithm)
{
    std::ifstream fp(file);
    if (!fp.is_open())
    {
        std::cerr << "File not found" << std::endl;
        return;
    }

    std::cout << "Compressing file: " << file << std::endl;
    if (!algorithm.empty() && algorithm == "l")
    {
        std::cout << "Using LZW algorithm" << std::endl;
        // Appel à la fonction de compression LZW (à implémenter)
    }
    else
    {
        std::cout << "Using Huffman algorithm" << std::endl;

        std::string data((std::istreambuf_iterator<char>(fp)), std::istreambuf_iterator<char>());

        fp.close();

        Huffman huffman;
        huffman.buildFrequencyTable(data);
        huffman.buildHuffmanTree();

        std::unordered_map<char, std::string> huffmanCodes;
        huffman.generateCodes(huffman.getRoot(), "", huffmanCodes);

        // encode the data
        std::string encodedData;
        for (char c : data)
        {
            encodedData += huffmanCodes[c];
        }
        // write the binary data to a file
        std::ofstream outFile(file + ".huff", std::ios::binary);
        if (!outFile.is_open())
        {
            std::cerr << "Cannot open output file" << std::endl;
            return;
        }

        // write the size of the original data to the file
        uint32_t dataSize = data.size();
        outFile.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));



        // write the huffman tree code to the file
        uint32_t tableSize = huffmanCodes.size();
        outFile.write(reinterpret_cast<const char *>(&tableSize), sizeof(tableSize));
        for (const auto &pair : huffmanCodes)
        {
            outFile.put(pair.first);
            uint8_t codeLength = pair.second.size();
            outFile.put(codeLength);
            outFile.write(pair.second.c_str(), codeLength);
        }

        // write the encoded data to the file
        std::vector<uint8_t> binaryData((encodedData.size() + 7) / 8);
        for (size_t i = 0; i < encodedData.size(); ++i)
        {
            if (encodedData[i] == '1')
            {
                binaryData[i / 8] |= (1 << (7 - (i % 8)));
            }
        }
        outFile.write(reinterpret_cast<const char *>(binaryData.data()), binaryData.size());

        // display the original size and the compressed size
        std::cout << "Original size: " << data.size() << " bytes" << std::endl;
        std::cout << "Compressed size: " << binaryData.size() + sizeof(dataSize) + sizeof(tableSize) + tableSize * (1 + sizeof(uint8_t) + sizeof(char)) << " bytes" << std::endl;
        
        outFile.close();

    }
}
