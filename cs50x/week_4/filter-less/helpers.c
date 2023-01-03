#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float storage;

    // For loops to get every position of height and width at the 2d array "image"
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Storage variable receive the value of the sum of all the color channel at that position of the 2d array "image"
            storage = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;

            // We, then, store at each color channel of that position of the "image" 2d array the value at the "storage" variable
            // Rounded and divided by the number of elements summed
            image[i][j].rgbtBlue = round(storage / 3);
            image[i][j].rgbtGreen = round(storage / 3);
            image[i][j].rgbtRed = round(storage / 3);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    // Create a storage variable for each color channel
    float red_storage, green_storage, blue_storage;

    // For loops to get every position of height and width at the 2d array "image"
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Sepia Blue || Equation that leads to a blue value of sepia
            blue_storage = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);

            // See if the value of blue_storage goes over the maximum quantity allowed by 8 bits
            if (blue_storage > 255)
            {
                blue_storage = 255;
            }

            // Sepia Green || Equation that leads to a green value of sepia
            green_storage = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);

            // See if the value of green_storage goes over the maximum quantity allowed by 8 bits
            if (green_storage > 255)
            {
                green_storage = 255;
            }

            // Sepia Red || Equation that leads to a red value of sepia
            red_storage = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);

            // See if the value of red_storage goes over the maximum quantity allowed by 8 bits
            if (red_storage > 255)
            {
                red_storage = 255;
            }

            // Give the value of each "storage" variable to its respective channel at that positon of "image" 2d array
            image[i][j].rgbtBlue = round(blue_storage);
            image[i][j].rgbtGreen = round(green_storage);
            image[i][j].rgbtRed = round(red_storage);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // Creat a new RGBTRIPLE struct to receive a copy of the content of the "image" 2d array
    RGBTRIPLE image_copy[height][width];

    // For loops to get every position of height and width at the 2d array "image"
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // At each position, store the value there in the same postion at image_copy at every color channel
            image_copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    // For loops to get every position of height and width at the 2d array "image"
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Each position of the 2d "image array" receives the pixel oposite to that position found in the "image_copy" 2d array
            // We must use a copy here beacause, at each iteration, the original "imatge" 2d array keep changing do to the neu pixels received
            // At the middle point, the pixels copied would be the same ones already copied before
            // 1/10 2/9 3/8 4/7 5/6 |middle| 6/5 7/4 8/3 9/2 10/1
            // Copy every color channel
            image[i][j].rgbtBlue = image_copy[i][(width - 1) - j].rgbtBlue;
            image[i][j].rgbtGreen = image_copy[i][(width - 1) - j].rgbtGreen;
            image[i][j].rgbtRed = image_copy[i][(width - 1) - j].rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Create a storage variable for each color channel
    float blue_storage, green_storage, red_storage;

    // Create a variable to be incremented
    int increment;

    // Creat a new RGBTRIPLE struct to receive a copy of the content of the "image" 2d array
    RGBTRIPLE image_copy[height][width];

    // For loops to get every position of height and width at the 2d array "image"
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // At each position, store the value there in the same postion at image_copy at every color channel
            image_copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    // For loops to get every position of height and width at the 2d array "image"
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // At each width postion, restore all variables values to 0
            blue_storage = 0;
            green_storage = 0;
            red_storage = 0;

            increment = 0;

            // Loops to iterate a 3x3 grid of pixels arround the pixel at that position, including the selected pixel
            for (int height_3x3 = i - 1; height_3x3 <= i + 1; height_3x3++)
            {

                for (int width_3x3 = j - 1; width_3x3 <= j + 1; width_3x3++)
                {

                    // Check if any value of width and/or height exceed the limit or has a value smallers then the minimum
                    // If so. continue to the next iteration of the loop and check again
                    if (width_3x3 < 0 || width_3x3 > width - 1 || height_3x3 < 0 || height_3x3 > height - 1)
                    {
                        continue;
                    }

                    // If the if check is not triggered, store the sum of the pixel at that position and collor channel
                    //  with the value at each color channel storage
                    red_storage = red_storage + image_copy[height_3x3][width_3x3].rgbtRed;

                    green_storage = green_storage + image_copy[height_3x3][width_3x3].rgbtGreen;

                    blue_storage = blue_storage + image_copy[height_3x3][width_3x3].rgbtBlue;

                    // When all values are stored, increment by one
                    increment++;

                }
            }

            // Every iteration of every color channel of the "image" 2d array receives its respective color storage value
            // Rounded and divided by the value of "increment"check50 cs50/problems/2022/x/filter/less
            image[i][j].rgbtRed = round(red_storage / increment);
            image[i][j].rgbtGreen = round(green_storage / increment);
            image[i][j].rgbtBlue = round(blue_storage / increment);
        }
    }

    return;
}
