#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
int score;

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");
    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    //printf("Score 1 is %i, Score 2 is %i\n", score1, score2);
    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int n = strlen(word);
    int j;
    score = 0;
    for (int i = 0; i < n ; i++)
    {
        if (isupper(word[i]))
        {
            word[i] = tolower(word[i]);
        }
        if (islower(word[i]))
        {
            j = word[i] - 97;
            //printf("Letter %c is worth %i Points\n", word[i], POINTS[j]);
            score = score + POINTS[j];
        }
    }
    return score;
}