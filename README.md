# MiniCompressor

MiniCompressor is a simple file compression and decompression tool that currently supports the Huffman algorithm. This project demonstrates the implementation of basic data compression techniques.

## Features

- **Compression**: Compresses files using the Huffman coding algorithm.
- **Decompression**: Decompresses files that were compressed using the Huffman algorithm.

## Project Structure

README.md
markdown
Copier le code
# MiniCompressor

MiniCompressor is a simple file compression and decompression tool that currently supports the Huffman algorithm. This project demonstrates the implementation of basic data compression techniques.

## Features

- **Compression**: Compresses files using the Huffman coding algorithm.
- **Decompression**: Decompresses files that were compressed using the Huffman algorithm.

## Project Structure

    MiniCompressor/
    ├── include/
    │ ├── compressor.h
    │ ├── decompressor.h
    │ ├── huffman.h
    │ └── ...
    ├── src/
    │ ├── compressor.cpp
    │ ├── decompressor.cpp
    │ ├── huffman.cpp
    │ ├── ...
    │ └── main.cpp
    ├── test/
    │ ├── test_huffman.cpp
    │ └── ...
    ├── obj/
    ├── bin/
    ├── README.md
    └── Makefile


## Requirements

- A C++ compiler with C++17 support (e.g., GCC 7.1 or later)
- CMake (optional, if you use the provided Makefile)
- Google Test (for running unit tests)

## Installation

1. **Clone the repository**:
   ```sh
   git clone https://github.com/yaacovdev/MiniCompressor.git
   cd MiniCompressor
   ```
2. **Build the project**:
   ```sh
   make
   ```

## Usage
### Compress a file
To compress a file using the Huffman algorithm:
```sh
bin/MiniCompressor -c h -f /path/to/your/file.txt
   ```
This will create a compressed file with the `.huff` extension.


### Decompress a file
To decompress a file compressed using the Huffman algorithm:

```sh
bin/MiniCompressor -d h -f /path/to/your/file.txt.huff
```
This will create a decompressed file with the same name as the original file, prefixed with `d_`.

## Example
To compress a file `test.txt`:

```sh
bin/MiniCompressor -c h -f test.txt
```
To decompress the file `test.txt.huff`:

```sh
bin/MiniCompressor -d h -f test.txt.huff
```
## Running Tests
To run the unit tests:

```sh
make
./bin/MiniCompressorTest
```
## Future Work
- Implement LZW compression and decompression algorithms.
- Add more unit tests for comprehensive coverage.
- Improve error handling and user feedback.

## Contributing
Feel free to submit issues, fork the repository, and send pull requests. Contributions are welcome! 
Currently, I am the sole contributor to this project.

