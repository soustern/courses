#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// importing the function
int compute_score(string word);

int main(void)
{

    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Cheack if score is lesser, bigger or equal
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!\n");
    }

    // TODO: Print the winner
}

// Function to make all caracthers lowercase and assign the respective value of points to its respective letter
int compute_score(string word)
{
    // Initializing the variable in wich the sum of numbers will be stored to 0
    int sum = 0;

    // Loop ta goes around the amount of caracters there is at the string passed
    for (int i = 0, n = strlen(word); i < n; i++)
    {

        // Cast char data type ins index i of string "word" || check if that position contains a uppercase || if so, convert it to lower and stores it at the same position
        if (isupper((char)word[i]) != 0)
        {
            word[i] = tolower((char)word[i]);
        }

        // Below are if/eslse statements that checks if the character stored in index i of string "word" is equal to a certain value of the ASCII board || If so, assign a specific value
        if (word[i] == 97 || word[i] == 101 || word[i] == 105 || word[i] == 108 || word[i] == 110 || word[i] == 111 || word[i] == 114)
        {
            word[i] = 1;
        }
        else if (word[i] == 115 || word[i] == 116 || word[i] == 117)
        {
            word[i] = 1;
        }
        else if (word[i] == 98 || word[i] == 99 || word[i] == 109 || word[i] == 112 || word[i] == 98)
        {
            word[i] = 3;
        }
        else if (word[i] == 100 || word[i] == 103)
        {
            word[i] = 2;
        }
        else if (word[i] == 102 || word[i] == 104 || word[i] == 118 || word[i] == 119 || word[i] == 121)
        {
            word[i] = 4;
        }
        else if (word[i] == 106 || word[i] == 120)
        {
            word[i] = 8;
        }
        else if (word[i] == 107)
        {
            word[i] = 5;
        }
        else if (word[i] == 113 || word[i] == 122)
        {
            word[i] = 10;
        }

        // If there is no correspodante at ASCII board, store 0 at that same position
        else
        {
            word[i] = 0;
        }

        // Create a variable just to store the new value attributed to position i of string"word" (now converted to char and receiving integers)
        int storage = word[i];

        // Store the sum at the sum variable
        sum = sum + storage;
    }

    // Return the sum variable
    return sum;

}

