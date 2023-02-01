#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Discriminating asccii values for upper and lower case letters
int ascii_lower[] = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};
int ascii_upper[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};

// Importing functions
string plain_to_cypher(string encryptor, string plaintext);

// Program that takes a custom key, wich must adhere to certain rule, as inpur, than takes plaintext as input and return the same plaintext encrypted in conformity to the key given
int main(int argc, string argv[])
{

    // Declaring variables
    string string_storage = argv[1];

    // Start of checks ------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Check if there are two arguments inserted on terminal
    if (argc == 2)
    {

        // Cheking if argv has 26 characters in total
        if (strlen(argv[1]) == 26)
        {
            // Check if there are only alphabetical numbers with loop that loop for the amount of characters present in the key provided
            for (int i = 0, n = strlen(argv[1]); i < n; i++)
            {

                // Check if current index of array has only alphabetical value
                if ((string_storage[i] >= 97 && string_storage[i] <= 122) || (string_storage[i] >= 65 && string_storage[i] <= 90))
                {

                    // Check if current array index has a value equal to any other index on that same array || Index compared should be the one present in i and the next one beyond, never the same (must be i == i + 1)
                    for (int j = i + 1; j < n; j++)
                    {

                        // Set value to lowercase universally just to simplificate comparisson || If we find a equal pair of value following the loop structure above, an error is returned
                        if (tolower(string_storage[i]) == tolower(string_storage[j]))
                        {
                            printf("Key must not have two or more equal letters\n");
                            //printf("i:%i j:%i\n", string_storage[i], string_storage[j]);
                            return 1;
                        }
                    }

                }

                else
                {
                    printf("Key must contain only alphabetical characters\n");
                    return 1;
                }
            }

        }

        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // End of checks ------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Set plaintext value to user input || set cyphertext value to the return on function "plain_to_cypher"
    string plaintext = get_string("Plaintext: ");
    string cyphertext = plain_to_cypher(argv[1], plaintext);

    printf("ciphertext: %s\n", cyphertext);

}

// Function to test if each array index value is contemplated on the key provided || If so, that same value is exchanged with the value estipulated in the key
string plain_to_cypher(string encryptor, string plaintext)
{

    // Loop to iterate each character present in the plaintext user input
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        //printf("first iterator: %i\n", i);
        //printf("%i\n", plaintext[i]);

        // Checking if plaintext[i] is a letter
        if ((plaintext[i] >= 97 && plaintext[i] <= 122) || (plaintext[i] >= 65 && plaintext[i] <= 90))
        {
            // Checking if lowercase
            if (islower(plaintext[i]) != 0)
            {

                // Loop that goes for the total amount of letters on the alphabet
                for (int j = 0; j < 26; j++)
                {

                    // At each iteration, a variable made only for storage receiveis all the values of ascii lowercase alphabet
                    // This is necessary so the original ascii value doesnt get contaminated with the encrypted ones each iteration
                    int ascii_storage[] = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};

                    // Condition to see at wich postion that plaintext[i] appars on the ascii_storage list
                    if (plaintext[i] == ascii_storage[j])
                    {

                        // After we find it, we exchance that ascii_storage value by the one existent on the same position at the key provided
                        ascii_storage[j] = encryptor[j];

                        // Then that plaintext position receives the now exchanged ascii_value || we also force lowercase on that value existent on the key so we retain the user input
                        // If lowercase, it stays that way, even if the value being received from the key isnt
                        plaintext[i] = tolower(ascii_storage[j]);

                        // Condition braks so we dont iterate more once the positions are found and values are exchanged
                        break;
                    }

                }
            }

            // Checking if uppercase
            if (isupper(plaintext[i]) != 0)
            {

                // Loop that goes for the total amount of letters on the alphabet
                for (int j = 0; j < 26; j++)
                {

                    // At each iteration, a variable made only for storage receiveis all the values of ascii uppercase alphabet
                    // This is necessary so the original ascii value doesnt get contaminated with the encrypted ones each iteration
                    int ascii_storage[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};

                    // Condition to see at wich postion that plaintext[i] appars on the ascii_storage list
                    if (plaintext[i] == ascii_storage[j])
                    {

                        // After we find it, we exchance that ascii_storage value by the one existent on the same position at the key provided
                        ascii_storage[j] = encryptor[j];

                        // Then that plaintext position receives the now exchanged ascii_value || we also force uppercase on that value existent on the key so we retain the user input
                        // If uppercase, it stays that way, even if the value being received from the key isnt
                        plaintext[i] = toupper(ascii_storage[j]);

                        // Condition braks so we dont iterate more once the positions are found and values are exchanged
                        break;
                    }
                }
            }
        }
    }

    // We return the newly encrypted plaintext string
    return plaintext;
}


