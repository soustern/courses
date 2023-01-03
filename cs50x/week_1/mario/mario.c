#include <stdio.h>
#include <cs50.h>

int main(void) {

    // Variables
    int n;

    /*do
    {
        n = get_int("Size: ");
    }
    while (n < 1);*/

    while(true)
    {
        n = get_int("Size: ");
        if (n > 0)
        {
            break;
        }
    }

    // For each row
    for (int i = 0; i < n ; i++)
    {
        // For each column
        for(int j = 0; j < n; j++)
        {
            // Print a brick
            printf("#");
        }
        printf("\n");
    }
    // Move to next row
    printf("\n");
}