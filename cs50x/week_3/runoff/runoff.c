#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

// Program to simulate a runoff election
int main(int argc, string argv[])
{
    // Check for invalid usage
    // User input has only the name of the program and no candidate inserted
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    // The number of candidate recevies the argc value minus 1 to exclude the name of the program (./runoff)
    candidate_count = argc - 1;

    // If we have a number of candidates bigger than the const MAX_CANDIDATES (9), we return an error
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    // Iterate the candidates array for the lenght of candidate_count (Total number of candidates in argc - 1)
    for (int i = 0; i < candidate_count; i++)
    {

        // At each iteration, we update the .name value with use input ant we make it so the .votes values is 0 and .eliminated value is false
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    // voter_count variable receives user input
    voter_count = get_int("Number of voters: ");

    // If we exceed the number if voters discriminated at const MAX_VOTERS (100), we returna an error
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    // Loop that goes the amount of voters there are in the session
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            // At this point, we call the vote function and check if it returns true, if not, we execute the conditions code
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {

            // If won, break while loop
            break;
        }

        // Store the find_min function returned value int he int min variable
        // Check if we can decide a tie with that value passed to the function is_tie
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {

            // Iterate the candidates array for the lenght of candidate_count (Total number of candidates in argc - 1)
            for (int i = 0; i < candidate_count; i++)
            {

                // Printf all the names of the candidates wich are tied in their votes and are not eliminated
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }

            // We break the while loop at this point because the poll is finished
            break;
        }

        // Eliminate anyone with smallest number of votes
        eliminate(min);

        // Reset vote counts back to zero
        // We do this so we can safely judge the biggest and smallest number of votes again when this while loop loops
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}





// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    // Iterate the candidates array for the lenght of candidate_count (Total number of candidates in argc - 1)
    for (int i = 0; i < candidate_count; i++)
    {

        // Compare the name given with that iteration of the candidades[].name array value || If that name exists in the array, it executes code inside conditiom
        // Strcmp (string compare) used to compare both strings
        if (strcmp(name, candidates[i].name) == 0)
        {

            // Preferences array index with this voter in this ranking gets the value of the iteration i at this moment
            // Made this way because the candidates[].name position will be the same as the i iteration, so we can reference its position and store it
            preferences[voter][rank] = i;

            // Return true
            return 1;
        }
    }

    // Return False
    return 0;
}





// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

    // Loop that goes the amount of voters there are in the session
    for (int i = 0; i < voter_count; i++)
    {

        // If candidate indexed in the voter i and rank 0 of preference array is eliminated, execute the condition code
        if (candidates[preferences[i][0]].eliminated == true)
        {

            // Iterate the candidates array for the lenght of candidate_count (Total number of candidates in argc - 1)
            // This loop is used to check of the candidate of the first rank is eliminated
            // If so, we update that rank to the candidate at the next rank
            for (int j = 0; j < candidate_count; j++)
            {

                // If the candidate indexed at the same voter but different rank is not eliminated, we execute the condition code
                if (candidates[preferences[i][j]].eliminated == false)
                {

                    // We pass the value of that rank to the first rank
                    preferences[i][0] = preferences[i][j];

                    // We increment the number of votes for the candidate at that index by one
                    candidates[preferences[i][0]].votes++;

                    // We, then. break the loop to stop iterating
                    break;
                }
            }
        }
        else
        {

            // If candidate indexed in the voter i and rank 0 of preference array is not eliminated
            // We increment the number of votes of that candidate by one
            candidates[preferences[i][0]].votes++;
        }
    }

    return;
}





// Print the winner of the election, if there is one
bool print_winner(void)
{

    // Iterate the candidates array for the lenght of candidate_count (Total number of candidates in argc - 1)
    for (int i = 0; i < candidate_count; i++)
    {

        // If the number of votes of the candidate at i index is higher thant half of the total numbers of votes, thats the winner
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}





// Return the minimum number of votes any remaining candidate has
int find_min(void)
{

    // Variable tha will receive the MAX_VOTERS const + 1 || Made it this way so this variable always beggin with a number bigger than the biggest
    // value possible on candidates.vote (with is MAX_VOTERS)
    int min_num = MAX_VOTERS + 1;

    // Iterate the candidates array for the lenght of candidate_count (Total number of candidates in argc - 1)
    for (int i = 0; i < candidate_count; i++)
    {

        // Condition to check if candidate at that index is not eliminated
        // We do that so we dont update min_num with the value of a already eliminated candidate
        if (candidates[i].eliminated == false)
        {

            // If min_num is higher than the value of the number of vote of that candidate in that index
            // We update the min_num with the value of the quantity of votes at this index
            // Min_num will always have its value updated in the first iteration, because it begins with a BIG number, impossible to match
            if (min_num > candidates[i].votes)
            {
                min_num = candidates[i].votes;
            }
        }
    }

    // We return the value of min_num at that point
    return min_num;
}





// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{

    // Iterate the candidates array for the lenght of candidate_count (Total number of candidates in argc - 1)
    for (int i = 0; i < candidate_count; i++)
    {

        // If the value at that iteration is bigger than the minum value passed from the find_min function
        // We can say that it is not a tie, otherwise the line above wouldnt happen
        if (min < candidates[i].votes)
        {

            // The function is false at this point
            return false;
        }
    }
    return true;
}





// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{

    // Iterate the candidates array for the lenght of candidate_count (Total number of candidates in argc - 1)
    for (int i = 0; i < candidate_count; i++)
    {

        // If the number of votes of the candidate at index i is equal to the value being passe by the find_min function
        // We update the value of .eliminated of the candidate at that index to treu and reset its votes value to 0
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
            candidates[i].votes = 0;
        }
    }
    return;
}