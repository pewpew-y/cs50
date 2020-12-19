#include<cs50.h>
#include<stdio.h>
#include<math.h>

int main(void)
{
    float dollars;
    do
    {
        dollars = get_float("Change Owed: ");
    }
    while (dollars < 0); //makes sure the input is positive
    int cents = round(dollars * 100); //converting dollars into cents
    int i = 0; //coin count
    while (cents >= 25) //counting number of quarters required
    {
        cents -= 25;
        i++;
    }
    while (cents >= 10) //counting number of dimes required
    {
        cents -= 10;
        i++;
    }
    while (cents >= 5) //counting number of nickels required
    {
        cents -= 5;
        i++;
    }
    while (cents >= 1) //counting number of pennies required
    {
        cents -= 1;
        i++;
    }
    printf("%i\n", i);
}