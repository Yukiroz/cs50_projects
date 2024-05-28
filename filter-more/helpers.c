#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double average;
    int rnd;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            average = average / 3;
            rnd = round(average);
            image[i][j].rgbtRed = rnd;
            image[i][j].rgbtGreen = rnd;
            image[i][j].rgbtBlue = rnd;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //variable for reflect pixel
    int r;
    //temp variable for swap
    int temp;
    //loop on y axis
    for (int i = 0; i < height; i++)
    {
        //loop on x axis for half the row
        for (int j = 0; j < width / 2; j++)
        {
            r = width - 1 - j;
            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][r].rgbtRed;
            image[i][r].rgbtRed = temp;
            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][r].rgbtGreen;
            image[i][r].rgbtGreen = temp;
            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][r].rgbtBlue;
            image[i][r].rgbtBlue = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //temp copy 2D array
    RGBTRIPLE temp[height][width];
    //populate temp image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    double Red, Green, Blue;
    Red = 0;
    Green = 0;
    Blue = 0;
    int avgRed, avgGreen, avgBlue, counter;
    avgRed = 0;
    avgGreen = 0;
    avgBlue = 0;
    counter = 0;
    //blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //edge check
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    if (k >= 0 && l >= 0 && k < height && l < width)
                    {
                        Red = Red + temp[k][l].rgbtRed;
                        Green = Green + temp[k][l].rgbtGreen;
                        Blue = Blue + temp[k][l].rgbtBlue;
                        counter++;
                    }
                }
            }
            //avg calc
            Red = Red / counter;
            Green = Green / counter;
            Blue = Blue / counter;
            //round
            avgRed = round(Red);
            avgGreen = round(Green);
            avgBlue = round(Blue);
            //pixel blur
            image[i][j].rgbtRed = avgRed;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtBlue = avgBlue;

            //make 0
            Red = 0;
            Green = 0;
            Blue = 0;
            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;
            counter = 0;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //temp copy 2D array
    RGBTRIPLE temp[height][width];

    //populate temp image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    //Gx and Gy kernel
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //varriable for calcs
    double gxRed, gxGreen, gxBlue, gyRed, gyGreen, gyBlue;


    int row, column, sblRed, sblGreen, sblBlue;

    //edge
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //value reset 
            gxRed = 0;
            gxGreen = 0;
            gxBlue = 0;

            gyRed = 0;
            gyGreen = 0;
            gyBlue = 0;

            sblRed = 0;
            sblGreen = 0;
            sblBlue = 0;

            row = 0;

            //edge check
            for (int k = i - 1; k < i + 2; k++)
            {
                column = 0;

                for (int l = j - 1; l < j + 2; l++)
                {
                    if (k >= 0 && l >= 0 && k < height && l < width)
                    {
                        //Gx
                        gxRed = gxRed + Gx[row][column] * temp[k][l].rgbtRed;
                        gxGreen = gxGreen + Gx[row][column] * temp[k][l].rgbtGreen;
                        gxBlue = gxBlue + Gx[row][column] * temp[k][l].rgbtBlue;
                        //Gy
                        gyRed = gyRed + Gy[row][column] * temp[k][l].rgbtRed;
                        gyGreen = gyGreen + Gy[row][column] * temp[k][l].rgbtGreen;
                        gyBlue = gyBlue + Gy[row][column] * temp[k][l].rgbtBlue;
                    }
                    column++;
                }
                row++;
            }
            //sobel calc
            sblRed = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            sblGreen = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            sblBlue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));

            //pixel edge
            image[i][j].rgbtRed = (sblRed > 255) ? 255 : sblRed;
            image[i][j].rgbtGreen = (sblGreen > 255) ? 255 : sblGreen;
            image[i][j].rgbtBlue = (sblBlue > 255) ? 255 : sblBlue;

        }
    }

    return;
}
