#include<cs50.h>
#include<stdio.h> //linking to the respective libraries

int main(void)
{
    int n, i, j, k; //declaring variables to be used
    do
    {
        n = get_int("Height:"); //prompting the user for input
    }
    while (n < 1 || n > 8); //repeating until the condition is satisfied

    for (i = 0; i < n; i++) //this loop controls the column
    {
        for (j = i + 1; j < n; j++) //this loop adds spaces
        {
            printf(" ");
        }
        for (k = 0; k < 2; k++) //this loop is to print the hashes for the second time in the same row
        {
            for (j = 0; j < i + 1; j++) //this loop prints the #
            {
                printf("#");
            }
            if (k == 0) //this gives gap between adjacent pyramids equivalent to two hashes
            {
                printf("  ");
            }
        }
        printf("\n"); //it shifts the cursor to the next line
    }
}