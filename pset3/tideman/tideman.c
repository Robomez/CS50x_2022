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
void print_winner(void);
bool cycled(int tested_winner, int base_loser);

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

    // Query for votes every voter
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
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // If name is a match for the name of a valid candidate, update the ranks array...
    // ... to indicate that the voter has the candidate as their rank preference...
    // ... (where 0 is 1st pref, 1 is 2nd, etc.)
    // ranks[i] represents the user's ith preference
    // return true if rank was successfully recorded
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
    // update global prefs. preferences[i][j] - number of voters who prefer cand i over cand j

    // But here in loops i is just row number in matrix. j - column number.
    // !! ranks[i] - candidate's number.
    // So to update preferences of candidate pairs use preferences[ranks[i]][ranks[j]]
    // And no need to compare if rank is bigger because for each voter ranks[i] is preferred to ranks[i + 1]...
    // ... until ranks [candidate_count - 1]. So do preferences[ranks[i]ranks[i + 1]]++...
    // ... then preferences[ranks[i]ranks[i + 2]]++ and so on for every i from 0 to (candidate_count - 1).

    // for every candidate in ranks 0 to (cand_count - 1).
    for (int i = 0; i < candidate_count; i++)
    {
        // add its preference to cands (i + 1) (i + 2) ... (cand_count - 1) to preference
        for (int j = i + 1; j < candidate_count; j++)
        {
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // if one cand is preferred, add pair of cands to the pairs array. If tied, do not add.
    // function updates global variable pair_count to be the number of candidate pairs.
    // The pairs thus should all be stored between pairs[0] and pairs[pair_count - 1], inclusive.
    // Pair count is 0 in the beginning
    // Here i and j are ok because we just scroll through the matrix and save pairs.

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Strength of victory is defined by number of voters who prefer the preferred cand.
    // If multiple pairs have the same strength of vict, assume the order doesn't matter
    int counter = 1, pairs_left = pair_count;
    do
    {
        counter = 0;
        for (int i = 0; i < (pairs_left - 1); i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                int temp_win = pairs[i + 1].winner;
                int temp_los = pairs[i + 1].loser;
                pairs[i + 1].winner = pairs[i].winner;
                pairs[i + 1].loser = pairs[i].loser;
                pairs[i].winner = temp_win;
                pairs[i].loser = temp_los;
                counter++;
            }
        }
        pairs_left--;
    }
    while (counter != 0);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Create a locked graph, adding all edges in decreasing order of vict strength...
    // ... so long as the edge would not create a cycle.

    // For every pair
    for (int i = 0; i < pair_count; i++)
    {
        // Check for locked graph cycle. If not cycled, lock that pair.
        if (cycled(pairs[i].winner, pairs[i].loser) == false)
        {
            // Lock pair
            locked [pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Check for a cycle
bool cycled(int tested_winner, int base_loser)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If pairs winner (tested) is other locked pairs loser, check that pair
        if (locked[i][tested_winner])
        {
            // If that pairs winner is base pairs loser, than it's a loop
            if (i == base_loser)
            {
                return true;
            }
            else
            {
                // Test that pairs winner if it's locked as a loser to other candidate
                // Need to return value of recursive function
                if (cycled(i, base_loser) == true)
                {
                    return true;
                }
            }
        }
    }
    // If it doesn't happen to be a cycle, return false
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // Print name of the candidate who is the source of the graph. Assume not more than one source.
    // Source of the graph - this candidate is never locked as loser.
    for (int i = 0; i < candidate_count; i++)
    {
        int count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                count++;
            }
        }
        if (count == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
