#include <iostream>
#include <string>
#include "compressor.h"

void decompress(const std::string& file);

int main(int argc, char *argv[]) {
    std::cout << "MiniCompressor started" << std::endl;
    if (argc < 3) {
        std::cout << "-h for help" << std::endl;
        return 1;
    }

    std::string file;
    std::string action;
    std::string algorithm;

    for (int i = 1; i < argc; i++) { 
        if (std::string(argv[i]) == "-h") {
            std::cout << "Usage: minicompressor -c [OPTION] -f [FILE] -a [ALGORITHM]" << std::endl;
            return 0;
        } else if (std::string(argv[i]) == "-f" && i + 1 < argc) {
            file = argv[i + 1];
        } else if (std::string(argv[i]) == "-c" && i + 1 < argc) {
            action = argv[i + 1];
        } else if (std::string(argv[i]) == "-a" && i + 1 < argc) {
            algorithm = argv[i + 1];
        }
    }

    if (file.empty()) {
        std::cout << "File not specified" << std::endl;
        return 1;
    }

    if (action.empty()) {
        std::cout << "Compress/Decompress option not specified" << std::endl;
        return 1;
    }

    if (action == "c") {
        if (algorithm.empty()) {
            std::cout << "Algorithm not specified, using default Huffman" << std::endl;
            algorithm = "h";
        }

        compress(file, algorithm);
    } else if (action == "d") {
        std::cout << "Decompressing file" << std::endl;
        decompress(file);
    } else {
        std::cout << "Invalid option\n -h for help" << std::endl;
        return 1;
    }

    return 0;
}

void decompress(const std::string& file) {
    // std::ifstream fp(file);
    // if (!fp.is_open()) {
    //     std::cerr << "File not found" << std::endl;
    // } else {
    //     std::cout << "File found" << std::endl;
    //     // Ajoutez ici le code de décompression
    //     fp.close();
    // }
}
