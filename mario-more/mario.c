#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Variables
    int height;
    int n;
    //Ask for, Get and Check pyramid height (1-8)
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    //Print pyramid Loop
    for (int i = 1; i < height + 1; i++)
    {

        //Nested Loops
        //printing spaces
        n = height - i;
        while (n > 0)
        {
            printf(" ");
            n--;
        }
        //printing #
        n = i;
        while (n > 1)
        {
            printf("#");
            n--;
        }
        //prints #  #
        if (i > 0)
        {
            printf("#  #");
        }
        //printing hashes
        n = i;
        while (n > 1)
        {
            printf("#");
            n--;
        }
        if (i > 0)
        {
            printf("\n");
        }

    }
}