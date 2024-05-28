#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];


int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool cyclecheck(int winner, int loser);
void print_winner(void);
bool wcheck(int winner);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    //for (int i = 0; i < pair_count; i++)
    //{
    //    printf("Pair %i W:%i L:%i\n", i, pairs[i].winner, pairs[i].loser);
    //}
    //for (int i = 0; i < candidate_count; i++)
    //{
    //    for (int j = 0; j < candidate_count; j++)
    //    {
    //        printf("Pref %i-%i: %i ", i, j, preferences[i][j]);
    //    }
    //    printf("\n");
    //}
    sort_pairs();
    //for (int i = 0; i < pair_count; i++)
    //{
    //    printf("Pair %i W:%i L:%i\n", i, pairs[i].winner, pairs[i].loser);
    //}
    lock_pairs();
    //for (int i = 0; i < candidate_count; i++)
    //{
    //    for (int j = 0; j < candidate_count; j++)
    //    {
    //        printf("Lock %i-%i: %i ", i, j, locked[i][j]);
    //    }
    //    printf("\n");
    //}
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Look, compare, update, return
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (j > i)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                }
                else
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                }
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair sort[1];
    // sort by winner-loser, by preferences[pairs[i].winner][pairs[i].loser]
    for (int j = 0; j < pair_count; j++)
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (((preferences[pairs[i].winner][pairs[i].loser]) - (preferences[pairs[i].loser][pairs[i].winner])) <
                ((preferences[pairs[i + 1].winner][pairs[i + 1].loser]) - (preferences[pairs[i + 1].loser][pairs[i + 1].winner])))
            {
                sort[0].winner = pairs[i].winner;
                sort[0].loser = pairs[i].loser;
                pairs[i].winner = pairs[i + 1].winner;
                pairs[i].loser = pairs[i + 1].loser;
                pairs[i + 1].winner = sort[0].winner;
                pairs[i + 1].loser = sort[0].loser;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    //locked populate
    for (int i = 0; i < pair_count; i++)
    {
        if (!cyclecheck(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

//Check locked for cycles
bool cyclecheck(int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }
    for (int j = 0; j < pair_count; j++)
    {
        if (locked[loser][j])
        {
            if (cyclecheck(winner, j))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (wcheck(i))
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

//Winner recursion check
bool wcheck(int winner)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner])
        {
            return false;
        }
    }
    return true;
}