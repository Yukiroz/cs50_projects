#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Variables
    int size;
    int endsize = 0;
    int n = 0;
    // TODO: Prompt for start size
    do
    {
        size = get_int("Start size: ");
    }
    while (size < 9);
    //printf("Start size: %i\n", size);
    // TODO: Prompt for end size
    do
    {
        endsize = get_int("End size: ");
    }
    while (endsize < size);
    //printf("End Size: %i\n", endsize)
    // TODO: Calculate number of years until we reach threshold
    while (endsize > size)
    {
        size = size + (size / 3) - (size / 4);
        n++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", n);
}
