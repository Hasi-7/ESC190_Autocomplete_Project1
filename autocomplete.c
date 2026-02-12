#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *term1, const void *term2)
{
    const term *cterm1 = (const term *)term1;
    const term *cterm2 = (const term *)term2;
    return strcmp(cterm1->term, cterm2->term);
}

void read_in_terms(struct term **terms, int *pnterms, char *filename)
{
    // Initialization of required variables
    *pnterms = 0;
    char line[200];
    int i = 0;

    FILE *fp = fopen(filename, "r"); 
    fgets(line, sizeof(line), fp);
    *pnterms = atof(line);
    *terms = (term *)malloc(sizeof(term)*(*pnterms + 1));
    
    // Loops through the entire file until it reaches the last line (which is NULL)
    while (fgets(line, sizeof(line), fp) != NULL)
    { 
        // Gets the weight of each term
        (*terms + i)->weight = atof(line);

        // Split each line at the delimiter (tab)
        const char delimiter[2] = "\t";
        char *token;
        token = strtok(line, delimiter);

        // Gets the last element of the line that is split by the delimiter
        int count = 1;
        char temp[200];

        while (token != NULL) 
        {   
            if (count == 2)
            {
                strcpy(temp, token);
            }   

            count++;
            token = strtok(NULL, delimiter);
        }

        if (temp != NULL)   
        {
            strcpy((*terms + i)->term, temp);
        }

        i++;
    } 

    fclose(fp);

    //sort the terms in lexographic ascending order
    qsort(*terms, *pnterms, sizeof(term), compare);
}

int binary_search(term **terms, int nterms, char *substr)
{
    int low = 0;
    int high = nterms - 1;
    int mid;
    int comparison;
    
    while (low <= high)
    {
        mid = (int) ((high + low) / 2);
        comparison = strncmp((*terms + mid)->term, substr, strlen(substr));
        if (comparison == 0) 
        {
            break;
        }
        if (comparison < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return mid;
}

int lowest_match(struct term *terms, int nterms, char *substr)
{
    int best = binary_search(&terms, nterms, substr);
    while (strncmp((terms + best)->term, substr, strlen(substr)) == 0)
    {
        best--;
    }
    best++;
    return best;
}

int highest_match(struct term *terms, int nterms, char *substr)
{
    int best = binary_search(&terms, nterms, substr);
    while (strncmp((terms + best)->term, substr, strlen(substr)) == 0)
    {
        best++;
    }
    best--;
    return best;
}

int compare_answers(const void *weight1, const void *weight2)
{
    const term *cWeight1 = (const term *)weight1;
    const term *cWeight2 = (const term *)weight2;
    return -(cWeight1->weight - cWeight2->weight);
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr)
{   
    int high_match = highest_match(terms, nterms, substr);
    int low_match = lowest_match(terms, nterms, substr);


    *n_answer = high_match - low_match;
    *answer = (term *)malloc(sizeof(term)*(*n_answer));

    memcpy(*answer, terms + low_match, sizeof(term)*(*n_answer));

    qsort(*answer, *n_answer, sizeof(term), compare_answers);

}
