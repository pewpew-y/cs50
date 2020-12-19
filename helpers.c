#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculating the avg value of 3 colors
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swapping the values between pixels
            temp.rgbtBlue = image[i][j].rgbtBlue;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            temp.rgbtRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = temp.rgbtBlue;
            image[i][width - j - 1].rgbtGreen = temp.rgbtGreen;
            image[i][width - j - 1].rgbtRed = temp.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; //creating a copy of image to perform calculations on
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    int red, blue, green, i, j, k, l;
    float counter;

    for (i = 0; i < height; i++) //row
    {
        for (j = 0; j < width; j++) //column
        {
            red = blue = green = 0; //initial values of the pixel as 0
            counter = 0.00; //no. of values to calculate avg

            for (k = -1; k < 2; k ++) //controls the rows in the 3x3 box around the [i][j] pixel
            {
                for (l = -1; l < 2; l++) // control the columns for the same
                {
                    //checking if the particular pixel exists
                    if ((k + i) >= 0 && (j + l) >= 0 && (j + l) < width && (k + i) < height)
                    {
                        //if the pixel exists, then it's values are added and counter increases
                        red += temp[k + i][j + l].rgbtRed;
                        green += temp[k + i][j + l].rgbtGreen;
                        blue += temp[k + i][j + l].rgbtBlue;
                        counter++;
                    }
                }
            }
            //the avg values get assigned to the pixel
            image[i][j].rgbtBlue = round(blue / counter);
            image[i][j].rgbtGreen = round(green / counter);
            image[i][j].rgbtRed = round(red / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //creating a copy with an extra row and column on all sides so all pixels have a 3x3 box around them
    RGBTRIPLE temp[height + 2][width + 2];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i + 1][j + 1].rgbtBlue = image[i][j].rgbtBlue;
            temp[i + 1][j + 1].rgbtGreen = image[i][j].rgbtGreen;
            temp[i + 1][j + 1].rgbtRed = image[i][j].rgbtRed;
        }
    }
    //setting the values of extra pixels as 0
    for (int i = 0; i < (height + 2); i++)
    {
        for (int j = 0; j < (width + 2); j++)
        {
            if (i == 0 || j == 0 || i == (height + 1) || j == (width + 1))
            {
                temp[i][j].rgbtBlue = 0;
                temp[i][j].rgbtGreen = 0;
                temp[i][j].rgbtRed = 0;
            }
        }
    }

    float gxr, gyr, gxb, gyb, gxg, gyg;

    for (int i = 1; i < (height + 1); i++)//row
    {
        for (int j = 1; j < (width + 1); j++)//column
        {
            gxr = gyr = gxb = gyb = gxg = gyg = 0.00;
            for (int k = -1; k < 2; k++)//3x3 box row
            {
                for (int l = -1; l < 2; l++)//3x3 box column
                {
                    //multiplying the 3x3 box pixels with kernel values depending on it's position
                    if (k == -1 || k == 1)
                    {
                        gxb += temp[i + k][j + l].rgbtBlue * l;
                        gxg += temp[i + k][j + l].rgbtGreen * l;
                        gxr += temp[i + k][j + l].rgbtRed * l;
                    }
                    else if (k == 0)
                    {
                        gxb += temp[i + k][j + l].rgbtBlue * 2 * l;
                        gxg += temp[i + k][j + l].rgbtGreen * 2 * l;
                        gxr += temp[i + k][j + l].rgbtRed * 2 * l;
                        gyb += temp[i + k][j + l].rgbtBlue * 0;
                        gyg += temp[i + k][j + l].rgbtGreen * 0;
                        gyr += temp[i + k][j + l].rgbtRed * 0;
                    }

                    if (l == -1 || l == 1)
                    {
                        gyb += temp[i + k][j + l].rgbtBlue * k;
                        gyg += temp[i + k][j + l].rgbtGreen * k;
                        gyr += temp[i + k][j + l].rgbtRed * k;
                    }
                    else if (l == 0)
                    {
                        gyb += temp[i + k][j + l].rgbtBlue * 2 * k;
                        gyg += temp[i + k][j + l].rgbtGreen * 2 * k;
                        gyr += temp[i + k][j + l].rgbtRed * 2 * k;
                    }
                }
            }
            //calculating gx2 + gy2
            gxb = pow(gxb, 2) + pow(gyb, 2);
            gxg = pow(gxg, 2) + pow(gyg, 2);
            gxr = pow(gxr, 2) + pow(gyr, 2);

            //assigning the integral root of the values
            gxb = round(sqrt(gxb));
            gxg = round(sqrt(gxg));
            gxr = round(sqrt(gxr));

            //capping the values
            if (gxb > 255)
            {
                gxb = 255;
            }
            if (gxg > 255)
            {
                gxg = 255;
            }
            if (gxr > 255)
            {
                gxr = 255;
            }

            image[i - 1][j - 1].rgbtBlue = gxb;
            image[i - 1][j - 1].rgbtGreen = gxg;
            image[i - 1][j - 1].rgbtRed = gxr;
        }
    }
    return;
}
