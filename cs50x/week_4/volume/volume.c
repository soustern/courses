// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// Function prototypes
void copy_header(FILE *first, FILE *second);
void change_volume(FILE *first, FILE *second, float volume);

int main(int argc, char *argv[])
{
    // Check command-line arguments (cant have more then 3 arguments)
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open the first file the user has provided
    // Store its memory address at the output pointer of FILE data type
    FILE *input = fopen(argv[1], "r");

    // If the command fopen returns null and not an address, execture the condition code
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Open the second file the user has provided
    // Store its memory address at the output pointer of FILE data type
    FILE *output = fopen(argv[2], "w");

    // If the command fopem returns null and not an address, execture the condition code
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Store the third argument given by the user (wich is the volume change specifier)
    // Transform it from string (argv is an array of strings) to float data type
    // Store it at factor variable
    float factor = atof(argv[3]);

    // Copy header from input file to output file
    copy_header(input, output);

    // Read samples from input file and write updated data to output file
    change_volume(input, output, factor);

    // Close files
    fclose(input);
    fclose(output);
}

// Copy the exact amount oF bytes (HEADER_SIZE) of the header of the first.wav files and writes it in second.wav
void copy_header(FILE *first, FILE *second)
{
    // Create a unsigned int variable with 1 byte of size (8 bits) and alloc a memory section the exact size of bytes a .wav file header contains
    // THis data type was used because, having only 1 byte of size, it allows better flexibility to store something unorthodox
    // Such as the size of the const HEADER_SIZER (44 bytes)
    // This is the heap storage way
    uint8_t *storage = malloc(HEADER_SIZE);

    // Read the header using the exact same amount of bytes it contain (44) as parameter and store it at the addres specified in storage pointer
    fread(storage, HEADER_SIZE, 1, first);

    // Take the data that was inserted in the address at storage pointer and insert it in the second file
    fwrite(storage, HEADER_SIZE, 1, second);

    // Release (free) the heap memory that was allocated at line 57
    free(storage);
}

// Multiply all the bytes the come after the header of the .wav file by the volume provided by user input (argv(3))
void change_volume(FILE *first, FILE *second, float volume)
{

    // Create a int variable with 2 byte of size (16 bits) and alloc a memory section the exact size of bytes a .wav file header contains
    // THis data type was used becouse it contains the exact same size each sample (wave lenghts) inside the .wav contains
    // THis is the heap storage way
    int16_t *storage = malloc(sizeof(int16_t));

    // We read exaclty 2 bytes of data per loop and store that at the addrres present in the storage point
    // This loop will break automatically once all of the file content is read
    while (fread(storage, sizeof(int16_t), 1, first))
    {

        // Take the content of the address present at storage pointer (we can access the cotent using the * symbol)
        // Multiply that value by the volume user input
        // Store the new value at that same address
        *storage = *storage * volume;

        // Take the data that was inserted in the address at storage pointer and insert it in the second file
        fwrite(storage, sizeof(int16_t), 1, second);
    }

    // Release (free) the heap memory that was allocated at line 77
    free(storage);
}
