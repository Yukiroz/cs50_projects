#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

const int HEADER_SIZE = 44;

WAVHEADER inputheader;

int main(int argc, char *argv[])
{
    // Ensure proper usage

    // TODO #1

    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading

    // TODO #2

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read header

    // TODO #3

    fread(&inputheader, sizeof(BYTE), HEADER_SIZE, input);

    // Use check_format to ensure WAV format

    // TODO #4

    if (check_format(inputheader) != 1)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing

    // TODO #5

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Write header to file

    // TODO #6

    fwrite(&inputheader, HEADER_SIZE, 1, output);

    // Use get_block_size to calculate size of block

    // TODO #7

    int blocksize = get_block_size(inputheader);
    //printf("Block size is: %i\n", get_block_size(inputheader));

    // Write reversed audio to file

    // TODO #8

    DWORD buffer[inputheader.subchunk2Size / blocksize];

    for (int i = 0; i < inputheader.subchunk2Size / blocksize; i++)
    {
        fread(&buffer[i], blocksize, 1, input);
    }

    for (int i = 0; i < inputheader.subchunk2Size / blocksize; i++)
    {
        fwrite(&buffer[inputheader.subchunk2Size / blocksize - 1 - i], blocksize, 1, output);
    }
    //close files

    fclose(input);
    fclose(output);

    return 0;
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int n = 0;

    n = header.numChannels * header.bitsPerSample / 8;

    return n;
}