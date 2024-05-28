#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


//Variables
float grade, l, s;
int letters, sentences, words, igrade;
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Get String of text
    string text = get_string("Text: ");
    //Count letters (call count letters)
    letters = count_letters(text);
    //printf("Letters: %i\n", letters);
    //Count words
    words = count_words(text);
    //printf("Words: %i\n", words);
    //Count sentences
    sentences = count_sentences(text);
    //printf("Sentences: %i\n", sentences);
    //Calculate l, s and grade based on Coleman-Liau formula
    l = (letters * 100.0) / words;
    s = (sentences * 100.0) / words;
    grade = 0.0588 * l - 0.296 * s - 15.8;
    //Round grade and print grade, make exception if grade < 1 or grade > 16
    //printf("Grade before rounding %f\n", grade);
    grade = round(grade);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        if (grade >= 16)
        {
            printf("Grade 16+\n");
        }
        else
        {
            igrade = grade;
            printf("Grade %i\n", igrade);
        }
    }
    //End
}
//count letters function
int count_letters(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}
int count_words(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isblank(text[i]))
        {
            words++;
        }
    }
    words++;
    return words;
}
int count_sentences(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}