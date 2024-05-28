#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Variables
    long credit, number, div;
    int n, i, j, sum, card;
    //Prompt for input
    credit = get_long("Number: ");
    number = credit;
    //Calculate checksum (loop)
    for (i = 1; i < 17 + 1; i++)
    {
        n = credit % 10;
        credit = credit - n;
        credit = credit / 10;
        if (i % 2 == 0)
        {
            n = n * 2;
            if (n > 9)
            {
                n = (n % 10) + 1;
            }
        }
        sum = sum + n;
        //printf("%i\n", n);
    }
    //printf("checksum: %i\n", sum);
    //Check for card length and starting digits
    credit = number;
    i = 0;
    while (credit > 0)
    {
        credit = credit / 10;
        i++;
    }
    credit = number;
    div = 1;
    for (j = 2; j < i; j++)
    {
        div = div * 10;
    }
    card = credit / div ;
    //Print AMEX, MASTERCARD, VISA, INVALID
    if ((i == 15) && (card == 34 || card == 37) && (sum % 10 == 0))
    {
        printf("AMEX\n");
    }
    else if ((i == 16) && (card == 51 || card == 52 || card == 53 || card == 54 || card == 55) && (sum % 10 == 0))
    {
        printf("MASTERCARD\n");
    }
    else if ((i == 13 || i == 16) && (card / 10 == 4) && (sum % 10 == 0))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    //printf("number of digits: %i\n", i);
    //printf("first 2 numbers: %i\n", card);
}