#include "decompressor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <filesystem>

void decompress(const std::string &file)
{
    std::ifstream fp(file);
    if (!fp.is_open())
    {
        std::cerr << "File not found" << std::endl;
        return;
    }

    std::cout << "Decompressing file: " << file << std::endl;
    if (file.find(".lzw") != std::string::npos)
    {
        std::cout << "Using " << std::endl;
    }
    else if (file.find(".huff") != std::string::npos)
    {
        std::cout << "Decompress Huffman algorithm" << std::endl;

        std::ifstream inFile(file, std::ios::binary);
        if (!inFile.is_open())
        {
            std::cerr << "Cannot open input file" << std::endl;
            return;
        }
        // read the size of the original data
        uint32_t dataSize;
        inFile.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));

        uint32_t tableSize;
        inFile.read(reinterpret_cast<char *>(&tableSize), sizeof(tableSize));

        // read the huffman tree code
        std::unordered_map<std::string, char> huffmanCodes;
        for (uint32_t i = 0; i < tableSize; ++i)
        {
            char character = inFile.get();
            uint8_t codeLength = inFile.get();
            std::string code(codeLength, ' ');
            inFile.read(&code[0], codeLength);
            huffmanCodes[code] = character;
        }

        // read the encoded data
        std::vector<uint8_t> binaryData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();

        // convert the binary data to a string of bits
        std::string encodedData;
        for (uint8_t byte : binaryData)
        {
            for (int i = 7; i >= 0; --i)
            {
                encodedData += ((byte >> i) & 1) ? '1' : '0';
            }
        }
        // decode the data
        std::string decodedData;
        std::string currentCode;
        for (char bit : encodedData)
        {
            currentCode += bit;
            if (huffmanCodes.find(currentCode) != huffmanCodes.end())
            {
                decodedData += huffmanCodes[currentCode];
                currentCode.clear();
            }
            if (decodedData.size() == dataSize)
            {
                break;
            }
        }

        // get the output file name
        std::filesystem::path filePath(file);
        std::string outputFile = filePath.stem().string();

        // write the decoded data to a file
        std::ofstream outFile("d_" + outputFile);
        if (!outFile.is_open())
        {
            std::cerr << "Cannot open output file" << std::endl;
            return;
        }
        outFile.write(decodedData.c_str(), decodedData.size());
        outFile.close();

        std::cout << "Decompression complete. Original size: " << dataSize << " bytes" << std::endl;
    }
}
// Path: src/huffman.cpp