#include <stdio.h>
#include <string.h>
#include "compressor.h"

void decompress(char *file);

int main(int argc, char *argv[])
{
    printf("MiniCompressor started\n");
    if (argc < 3)
    {
        printf("-h for help\n");
        return 1;
    }

    char *file = NULL;
    char *action = NULL;
    char *algorithm = NULL;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            printf("Usage: minicompressor -c [OPTION] -f [FILE] -a [ALGORITHM]\n");
            return 0;
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        {
            file = argv[i + 1];
        }
        else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
        {
            action = argv[i + 1];
        }
        else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc)
        {
            algorithm = argv[i + 1];
        }
    }

    if (file == NULL)
    {
        printf("File not specified\n");
        return 1;
    }

    if (action == NULL)
    {
        printf("Compress/Decompress option not specified\n");
        return 1;
    }

    if (strcmp(action, "c") == 0)
    {
        printf("Compressing file\n");
        compress(file, algorithm);
    }
    else if (strcmp(action, "d") == 0)
    {
        printf("Decompressing file\n");
        decompress(file);
    }
    else
    {
        printf("Invalid option\n -h for help\n");
        return 1;
    }

    if (algorithm != NULL)
    {
        if (strcmp(algorithm, "h") == 0)
        {
            printf("Huffman algorithm\n");
        }
        else if (strcmp(algorithm, "l") == 0)
        {
            printf("LZW algorithm\n");
        }
        else
        {
            printf("Huffman algorithm by default\n");
        }
    }

    return 0;
}

void decompress(char *file)
{
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("File not found\n");
    }
    else
    {
        printf("File found\n");
        // Ajoutez ici le code de décompression
        fclose(fp);
    }
}
