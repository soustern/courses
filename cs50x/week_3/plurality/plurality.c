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
        //vote(name, argc);

        // Check if name given was invalid
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

    // Loop that goes around the amount of candidates inserted in argv
    for (int i = 0; i < candidate_count; i++)
    {

        // Check each index of the candidates.name array, than compares it with the name given
        if (strcmp(name, candidates[i].name) == 0)
        {

            // If a match is found, the .vote session of that same array goes up one
            candidates[i].votes++;
            //printf("votes: %i\n", candidates[i].votes);
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{

    // Storage variable
    int vote_counter = 0;

    // Loop that goes around the amount of candidates inserted in argv
    for (int i = 0; i < candidate_count; i++)
    {

        // If vote counter has and value tha is less than thone in candidates[i].votes, it gest updated with that value
        if (vote_counter < candidates[i].votes)
        {
            vote_counter = candidates[i].votes;
        }
    }

    // Loop that goes around the amount of candidates inserted in argv
    for (int i = 0; i < candidate_count; i++)
    {

        // Every time the value of vote_counter is equal to the one at that array index, the .name of the struct is printed
        if (vote_counter == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }


}