#include <cs50.h>
#include <stdio.h>

// Program that makes two parallel pyramids
int main(void)
{

    // Variable for pyramid height
    int height = 0;

    // Variable for quantity of hash per row
    int increment_more = 0;

    // Variable for quantity of spaces per row
    int increment_less;

    // Get a number between 1 and 8 for height
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Make it so quantity of spaces per row is equal to height
    increment_less = height;

    // Loop for rows
    for (int i = 0; i < height; i++)
    {
        // Increment quantity of column(s) of hash per row per loop
        increment_more++;

        // Decrement value so column(s) of spaces per row become less per loop
        increment_less--;

        // Implement column(s) of spaces on the left side
        for (int j = 0; j < increment_less; j++)
        {
            printf(" ");
        }

        // Implement column(s) of hashs on the left side
        for (int j = 0; j < increment_more ; j++)
        {
            printf("#");
        }

        // Print two columns of space between each hash side
        printf("  ");


        // Implement column(s) of hashs on the right side
        for (int j = 0; j < increment_more; j++)
        {
            printf("#");
        }

        // Put a line break at the end of each row
        printf("\n");
    }
}