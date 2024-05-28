#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Variables
    string plaintext, ciphertext, key;
    int i, j;
    //Check for invalid command line arguments and return 1
    if (argc != 2)
    {
        printf("./substitution key\n");
        return 1;
    }
    //Check key length
    key = argv[1];
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    //Check for non-alphabetic characters
    i = 0;
    while (i < 26)
    {
        //printf("Key[i]= %i", key[i]);
        if (key[i] < 65 || (key[i] > 90 && key[i] < 97) || key[i] > 122)
        {
            printf("Key is invalid\n");
            return 1;
        }
        i++;
    }
    //Check for repeated characters (case-insensitive)
    i = 0;
    while (i < 26)
    {
        j = i + 1;
        while (j < 26)
        {
            //printf("Checking for Key %c\n", key[i]);
            if (islower(key[i]))
            {
                if (key[i] == key[j] || key[i] == key[j] - 32)
                {
                    //printf("Comparing Key %c with Key %c\n", key[i], key[j]);
                    return 1;
                }
            }
            if (isupper(key[i]))
            {
                if (key[i] == key[j] || key[i] == key[j] + 32)
                {
                    //printf("Comparing Key %c with Key %c\n", key[i], key[j]);
                    return 1;
                }
            }
            j++;
        }
        i++;
    }
    //Get String
    plaintext = get_string("plaintext: ");
    ciphertext = plaintext;
    //Encipher (preserve lowercase/uppercase, leave non-alphabetic characters as is)
    for (i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            j = plaintext[i] - 65;
            ciphertext[i] = toupper(key[j]);
            //printf("if1 is working\n");
        }
        if (islower(plaintext[i]))
        {
            j = plaintext[i] - 97;
            ciphertext[i] = tolower(key[j]);
            //printf("if2 is working\n");
        }
        else
        {
            ciphertext[i] = plaintext[i];
            //printf("else is working\n");
        }
    }
    //Print ciphertext
    printf("ciphertext: %s\n", ciphertext);
}