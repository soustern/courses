#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Importing all the functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int coleman_index(int letters, int words, int sentences);

int main(void)
{
    // Declaring all the variables
    int letter_amount, word_amount, sentence_amount, grade;

    // Gettin text passage from user
    string text = get_string("Text: ");

    // Assigning to each variable the value handed back by irs corresponding function
    letter_amount = count_letters(text);
    word_amount = count_words(text);
    sentence_amount = count_sentences(text);
    grade = coleman_index(letter_amount, word_amount, sentence_amount);

    // Checking the "grade" value to change dynamically the message printed
    if (grade >= 1 && grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

}

// Function to get total amount of letters
int count_letters(string text)
{

    // Declaring a variable that will serve as the counter of how many letters
    int increment = 0;

    // Loop going that receives the total amount of characters at the string "text" as parammeter
    for (int i = 0, n = strlen(text); i < n; i++)
    {

        // Checking for uppercase character in each index position at "text" string
        if (isupper(text[i]) != 0)
        {

            // Turning any uppercase to lowercase and handing back the converted character to the same index
            text[i] = tolower(text[i]);
        }

        // Checking to see if character exists between the scope of lowercase characters decimal correspondant at ASCII chart
        if (text[i] >= 97 && text[i] <= 122)
        {

            // If so, increment goes up, one more letter
            increment++;
        }
    }

    // Return the value of increment
    return increment;
}

// Function to get total amount of words
int count_words(string text)
{

    // Declaring a variable that will serve as the counter of how many words
    int increment = 0;

    // Loop going that receives the total amount of characters at the string "text" as parammeter
    for (int i = 0, n = strlen(text); i < n; i++)
    {

        // The parameter used to count words is the ASCII decimal value to "blank space", since thats a constant tha exists between different words
        if (text[i] == 32)
        {

            // At every "blank space" encountered, increment goes up, one more word
            increment++;
        }
    }

    // Check to see if the string begins with a space || that would not count as a word since it is at the beggining at nothing presceding it
    if (text[0] == 32)
    {

        // The first position of the array at the string "text" is checked || If a black space is encountered, word amount counter "increment" goes down one
        increment--;
    }

    // Check to see if the string ends with a space || On the next line we already give increment + 1 to acount for the last wolrd at a string
    if (text[strlen(text) - 1] == 32)
    {

        // The last position of the array at the string "text" is checked || If a black space is encountered, word amount counter "increment" goes down one
        increment--;
    }

    // Return increment + 1 to acount fot the last wolrd at a string || If this wasnt here, the last word at a string wouldnt be counted if there wasnt a artificial blank space after it (user inserted)
    return increment + 1;
}

// Function to get total amount of sentences
int count_sentences(string text)
{

    // Declaring a variable that will serve as the counter of how many sentences
    int increment = 0;

    // Loop going that receives the total amount of characters at the string "text" as parammeter
    for (int i = 0, n = strlen(text); i < n; i++)
    {

        // Checking if charatcter of that index is correspondant to the ASCII decimal values to . ! ?
        if (text[i] == 33 || text[i] == 63 || text[i] == 46)
        {

            // If any of those are encountered, the number of sentences goes up one.
            increment++;
        }
    }

    // Return the value of increment
    return increment;

}

// Function to get all quantities and use then on a equation tha gives, as a result, a integer refering to the grade level of such text
int coleman_index(int letters, int words, int sentences)
{
    int index;

    // In here, some of the values have to be converted from integer to float || Thats is because the division operations wouldnt be accurate otherwise
    // There would remain some decimal numbers || The final value is then rounded up to the closest integer and handed back to "index"
    index = round((0.0588 * (((float)letters / words) * 100)) - (0.296 * (((float)sentences / words) * 100)) - 15.8);

    // Index variable is returned
    return index;
}