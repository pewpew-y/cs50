#include<stdio.h>
#include<cs50.h> //connecting to the respective libraries

int main(void)
{
    string name = get_string("What's your name?\n"); //prompts the user for their name
    printf("Hello, %s\n", name); //says hello to the user
}