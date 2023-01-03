#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Defining a constant that has the size of a individual FAT memory block size
#define BLOCK_SIZE 512

// Defining the new data type BYTE
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Declare Storage (buffer) variable
    // Allocate 512 bytes of memory to it
    BYTE *storage = malloc(BLOCK_SIZE * sizeof(BYTE));

    // Check if malloc can get enough space to allocate the amount of memory asked
    // If not, it will return NULL address to *storage
    if (storage == NULL)
    {
        return 1;
    }

    // Create variable that will increment from 0
    int increment = 0;

    // Create the pointers that will receive the address in wich the files will be opened
    // We initialize the pointers to null so to avoid problems
    FILE *card = NULL;
    FILE *new_img = NULL;

    // String address in wich the name of the file name (that will formated by sprintf) wiil be stored
    // A memory section capable of containing up to 10 characters (counting \0) will be allocated to that adress
    char *filename = malloc(sizeof(char) * 10);

    // Check if malloc can get enough space to allocate the amount of memory asked
    // If not, it will return NULL address to *storage
    if (filename == NULL)
    {
        return 1;
    }

    // Check if user input is only the program name and the file name
    // Check if user did not input the required filename
    if (argc == 1 || argc > 2)
    {
        puts("Correct usage: ./recover your_file_name.extension");
        return 1;
    }

    // Open memory card file and store its address (returned by fopen) at the card pointer
    card = fopen(argv[1], "r");

    // Check if card opened correctly
    // If not, it will return a NULL address
    if (card == NULL)
    {
        puts("Could not open file.\n");
        return 1;
    }

    // While EOF is not reached, read the content of the "card" address opened file into "storage" address
    // Fread function returns the number of bytes it has read if success
    // THe while loop is also broken if fread returns a number smaller than 512 bytes
    // In this fread specification, we read 1 byte (sizeof(BYTE)) 512 times
    while (fread(storage, sizeof(BYTE), BLOCK_SIZE, card) == 512)
    {

        // Checking if block has the beggining of a jpeg
        // Checking if the first four bytes are the ones present on every jpeg header
        if (storage[0] == 0xff && storage[1] == 0xd8 && storage[2] == 0xff && (storage[3] & 0xf0) == 0xe0)
        {

            // Check if this is the first time a jpg is found
            if (increment == 0)
            {

                // Format and save a filename at the "filename" pointer that will dynamically change its value depending
                // The value if increment
                // Since we want to start saving from "000.jpg", we get the value of increment - 1
                sprintf(filename, "%03i.jpg", increment);

                // New file will be created // opened and it will have as its name the string stored at "filename"
                // "new_img" will receive its address at memory
                new_img = fopen(filename, "w");

                // Write the jpg header that is (at this moment) stored at "storage" variable address
                // Into the newly opened file
                fwrite(storage, sizeof(BYTE), BLOCK_SIZE, new_img);

                // Increment goes up by 1
                increment++;
            }

            // If it is not the first jpg found
            else
            {

                // Close any previously opened file
                fclose(new_img);

                // Update the name strang stored at "filename" (with increment - 1 to have the correct index value)
                sprintf(filename, "%03i.jpg", increment);

                // New file will be created // opened and it will have as its name the string stored at "filename"
                // "new_img" will receive its address at memory
                new_img = fopen(filename, "w");

                // Write the jpg header that is (at this moment) stored at "storage" variable address
                // Into the newly opened file
                fwrite(storage, BLOCK_SIZE, 1, new_img);

                // Increment goes up by 1
                increment++;
            }
        }

        // If current block is not the beggining of a jpg
        else
        {

            // Check if this is the first block and if it does not contain the header of a jpg
            if (increment == 0 && !(storage[0] == 0xff && storage[1] == 0xd8 && storage[2] == 0xff && (storage[3] & 0xf0) == 0xe0))
            {

                // If thats the case, go for the next iteration of this loop
                continue;
            }

            else
            {
                // Write the current block stored at "storage" address at the currently opened file
                fwrite(storage, sizeof(BYTE), BLOCK_SIZE, new_img);
            }
        }
    }

    // Check if fread has returned a number smaller than 512 bytes
    /* if (fread(storage, sizeof(BYTE), BLOCK_SIZE, card) != 512)
    {
        while (fread(storage, sizeof(BYTE), sizeof(BYTE), card))
        {

            // Write the current block stored at "storage" address at the currently opened file
            fwrite(storage, sizeof(BYTE), sizeof(BYTE), new_img);
        }
    } */

    // Release any allocated memory
    free(storage);
    free(filename);

    // Close any remaining file
    fclose(card);
    fclose(new_img);

    return 0;
}