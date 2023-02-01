#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Define maximum array size as an constant
#define MAX 16

// Import functions to validate cards
int check_amex(long card_num, float digit_number);
int check_visa(long card_number, float digit_number);
int check_visa_mastercard(long card_number, float digit_number);
int check_mastercard(long card_number, float digit_number);

// Validate credit card number and say of wich corporation it belongs to
int main(void)
{
    // Must be long so in can handle all the card number digits || Num store serves as a multipurpose number storage
    long card_num, num_store;

    // Must be a float so the round() function works out later in the code
    float increment;

    // Establishing arrays
    int num_odd[MAX];
    int num_even[MAX];

    // Making it so the last place in the array has a value of 0 so it can receive anything later on
    num_odd[15] = 0;
    num_even[15] = 0;


    // Get validated input || The total count of digits in the card number must not be different than 13, 15 or 16
    do
    {
        card_num = get_long("Card number: ");

        // Storing card number so it doesnt get lost || Must be reusable later
        num_store = card_num;

        // Giving the value of zero to increment so each passagr of this loop has an increment counting up from zero
        increment = 0;

        // Make it so the card number gest divided until it reaches zero
        do
        {
            num_store = num_store / 10;

            // On every disivison, increment goes up
            increment++;
        }
        while (num_store != 0);
        if (increment != 13 && increment != 15 && increment != 16)
        {
            printf("INVALID\n");
            return 0;
        }
    }
    while (increment != 13 && increment != 15 && increment != 16);

    // Reseting num_store value to the card number (user input)
    num_store = card_num;

    // Loop to get every other digit and store in array
    for (int i = 0; i < round(increment / 2); i++)
    {
        // Diving the entire number in groups of two || then getting the second-to-last number on those divisions
        num_odd[i] = (num_store % 100) / 10;

        // Each iteration of the array must have its value multiplied by 2
        num_odd[i] = num_odd[i] * 2;

        // After multiplication, if a number goes beyond one decimal (10), it must have its two digits summed up
        if (num_odd[i] > 9)
        {

            // Storing summed up digits in the same array the beyond one decimal value was in
            num_odd[i] = (num_odd[i] % 10) + (num_odd[i] / 10);
        }

        // Dividing card number by 100 so we get rid of the previous two digits we already processed previously in the loop
        num_store = num_store / 100;
    }

    // Loop to get the sum of every other digit
    for (int i = 0; i < round(increment / 2); i++)
    {

        // Store the sum of every odd digit in position 15 of the same array
        num_odd[15] = num_odd[15] + num_odd[i];
    }

    // Reseting num_store value to the card number (user input)
    num_store = card_num;

    // Loop to get the digits that werent taken in previous loop
    for (int i = 0; i < round(increment / 2); i++)
    {

        // Diving the entire number in groups of two || then getting the last number on those divisions
        num_even[i] = (num_store % 100) % 10;

         
        num_store = num_store / 100;
    }

    // Loop to get the sum of every not previously summed digit
    for (int i = 0; i < round(increment / 2); i++)
    {

        // Store the sum of every odd digit in position 15 of the same array
        num_even[15] = num_even[15] + num_even[i];
    }

    // Making sure the sum of both even and odd number is equal to zero
    if ((num_even[15] + num_odd[15]) % 10 == 0)
    {

        // Checking if total digit size of card number is 15 || that can only mean it is American Express
        if (increment == 15)
        {

            // Reseting num_store value to zero so it can receive another value
            num_store = 0;

            // num_store receiving the value that check_amex function returns
            num_store = check_amex(card_num, increment);

            // Checking if returneds value is equal to 37 or 34
            if (num_store == 37 || num_store == 34)
            {
                printf("AMEX\n");
                //printf("\n");
                return 0;
            }
            else
            {
                printf("INVALID\n");
            }
        }

        // Checking if total digit size of card number is 13 || that can only mean it is Visa
        else if (increment == 13)
        {

            // Reseting num_store value to zero so it can receive another value
            num_store = 0;

            // num_store receiving the value that check_visa function returns
            num_store = check_visa(card_num, increment);

            // Checking if returneds value is equal to 4
            if (num_store == 4)
            {
                printf("VISA\n");
                //printf("\n");
                return 0;
            }
        }

        // Checking if total digit size of card number is 16 || that  means it can be mastercard or visa
        else if (increment == 16)
        {

            // Reseting num_store value to zero so it can receive another value
            num_store = 0;

            // num_store receiving the value that check_visa_mastercard function returns
            num_store = check_visa_mastercard(card_num, increment);

            // Checking if returned value is equal to 4 || that means it is visa
            if (num_store == 4)
            {
                printf("VISA\n");
                //printf("\n");
                return 0;
            }

            // Checking if returned value is equal to 5 || that means it CAN BE mastercard
            else if (num_store == 5)
            {

                // Reseting num_store value to zero so it can receive another value
                num_store = 0;

                // num_store receiving the value that check_mastercard function returns
                num_store = check_mastercard(card_num, increment);

                // Checking if returneds value is between 51 and 55
                if (num_store > 50 && num_store < 56)
                {
                    printf("MASTERCARD\n");
                    //printf("\n");
                    return 0;
                }

                // If not whitin that range, thats a invalid card number
                else
                {
                    printf("INVALID\n");
                }
            }
        }
    }

    // If sum of odd and evens numbers is not equal to zero, it is an invalid card number
    else
    {
        printf("INVALID\n");
        //printf("\n");
        return 0;
    }
}

// Function to get first two digits of card number
int check_amex(long card_number, float digit_number)
{
    for (int i = 0; i < digit_number; i++)
    {

        // We keep dividing by until we reach a 2 digit value
        card_number = card_number / 10;
        if (card_number < 100)
        {
            break;
        }
    }
    //printf("%li\n", card_number);
    return card_number;
}

// Function to get first digit of card number
int check_visa(long card_number, float digit_number)
{
    for (int i = 0; i < digit_number; i++)
    {

        // We keep dividing by until we reach a 1 digit value
        card_number = card_number / 10;
        if (card_number < 10)
        {
            break;
        }
    }
    //printf("%li\n", card_number);
    return card_number;
}

// Function to get first digit of card number
int check_visa_mastercard(long card_number, float digit_number)
{
    for (int i = 0; i < digit_number; i++)
    {

        // We keep dividing by until we reach a 1 digit value
        card_number = card_number / 10;
        if (card_number < 10)
        {
            break;
        }
    }
    //printf("%li\n", card_number);
    return card_number;
}

// Function to get first two digits of card number
int check_mastercard(long card_number, float digit_number)
{
    for (int i = 0; i < digit_number; i++)
    {

        // We keep dividing by until we reach a 2 digit value
        card_number = card_number / 10;
        if (card_number < 100)
        {
            break;
        }
    }
    //printf("%li\n", card_number);
    return card_number;
}