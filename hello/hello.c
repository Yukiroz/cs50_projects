#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //question
    string name = get_string("What's your name? ");
    //answer
    printf("hello, %s\n", name);
}