#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<math.h>

int main(void)
{
    string text = get_string("Text: "); //prompting user for input

    float letters = 0, words = 1, sentences = 0; //initializing
    for (int i = 0, n = strlen(text); i < n; i++) //checking each character in the string to calculate
    {
        if (text[i] >= 'A' && text[i] <= 'Z') //calculates letters
        {
            letters++;
        }
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            letters++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?') // calculates sentences
        {
            sentences++;
        }
        else if (text[i] == ' ') // calculates words
        {
            words++;
        }
    }

    int index = round((0.0588 * (letters * 100 / words)) - (0.296 * (sentences * 100 / words)) - 15.8); //using the formula

    if (index < 1) //printing the desired result
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}