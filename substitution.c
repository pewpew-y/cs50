#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>

int main(int argc, string argv[])
{

    if (argc != 2) //makes sure key is given
    {
        printf("USAGE: ./substitution KEY\n");
        return 1;
    }
    int n = strlen(argv[1]);
    if (n != 26) //makes sure of length
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) //makes sure unrepeated alphabets
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabets.\n");
            return 1;
        }
        for (int j = i + 1; j < n; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must not contain repeated characters\n");
                return 1;
            }
        }
    }

    string alpha = "abcdefghijklmnopqrstuvwxyz"; //alphabets in order
    string plaintext = get_string("plaintext:"); //prompts user for input
    int m = strlen(plaintext);
    char cipher[m];
    for (int i = 0; i < m; i++) //does the encryption
    {
        if (isalpha(plaintext[i])) //if character is alphabet
        {
            if (islower(plaintext[i])) //if alpha is lowercase
            {
                int j = 0;
                while (plaintext[i] != alpha[j])
                {
                    j++;
                }
                cipher[i] = tolower(argv[1][j]);
            }
            else //if alpha is uppercase
            {
                int j = 0;
                while (plaintext[i] != toupper(alpha[j]))
                {
                    j++;
                }
                cipher[i] = toupper(argv[1][j]);
            }
        }
        else //if character is not alpha
        {
            cipher[i] = plaintext [i];
        }
    }
    printf("ciphertext:"); //output
    for (int i = 0; i < m; i++)
    {
        printf("%c", cipher[i]);
    }
    printf("\n");
    return 0;
}