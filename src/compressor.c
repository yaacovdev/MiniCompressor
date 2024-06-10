#include <stdio.h>
#include <string.h>
#include "compressor.h"

void compress(const char *file, const char *algorithm)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return;
    }

    printf("Compressing file: %s\n", file);
    if (algorithm != NULL && strcmp(algorithm, "l") == 0)
    {
        printf("Using LZW algorithm\n");
        // Appel à la fonction de compression LZW (à implémenter)
    }
    else
    {
        printf("Using Huffman algorithm\n");
        // Appel à la fonction de compression Huffman (à implémenter)
    }

    fclose(fp);
}