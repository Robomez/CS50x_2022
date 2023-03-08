#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // If name matches one of candidates[i].name, then update that candidate's vote total to accounte.
    // If name doesn't match any of candidates[i].name, no vote total should change.
    // The vote function should return true to indicate a successful ballot
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }


    // Vote function should return false to indicate an invalid ballot
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Find the max number of votes
    int count_max = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > count_max)
        {
            count_max = candidates[i].votes;
        }
    }

    // Print out the name of the candidate who received the most votes in the election, then print a new line.
    // If election ends in a tie, print the names of each of the winning candidates, each on a separate line
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == count_max)
        {
            printf("%s\n", candidates[j].name);
        }
    }
    return;
}
