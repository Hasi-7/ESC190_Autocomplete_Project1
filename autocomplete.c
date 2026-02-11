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
    *terms = (term *)malloc(sizeof(term));
    int capacity = 1;
    char line[200];
    FILE *fp = fopen(filename, "r"); 
    // Loops through the entire file until it reaches the last line (which is NULL)
    while (fgets(line, sizeof(line), fp) != NULL)
    { 
        // Gets the weight of each term
        (*terms + *pnterms)->weight = atof(line);
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
                // printf("Token: %s\n", temp);
            }   
            count++;
            token = strtok(NULL, delimiter);
        }
        if (temp != NULL)
        {
            strcpy((*terms + *pnterms)->term, temp);
        }
        (*pnterms)++;
        //  Increases capacity and reallocates memory for the terms in the file 
        // using the new capacity.
        if (*pnterms == capacity)
        {
            capacity *= 2;
            *terms = (term *)realloc(*terms, sizeof(term)*capacity);
        }
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
    char *src = (char *)malloc(sizeof(strlen(substr)));
    int comparison;
    
    while (low <= high)
    {
        mid = (int) ((high + low) / 2);
        // Uses the comparison function to compare a term in the block and a substr
        strncpy(src, (*terms + mid)->term, strlen(substr) + 1);
        comparison = strncmp((*terms + mid)->term, substr, strlen(substr));
        *(src + strlen(substr)) = '\0';
        //comparison = (compare((const void *)(&substr), (const void *)(&(src))));
        printf("%d, %s\n", comparison, src);
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
        //printf("%d\n", best);
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
        //printf("%d\n", best);
    }
    best--;
    return best;
}

int compare_answers(const void *weight1, const void *weight2)
{
    const term *cWeight1 = (const term *)weight1;
    const term *cWeight2 = (const term *)weight2;
    return cWeight1->weight - cWeight2->weight;
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr)
{   
    int high_match = highest_match(terms, nterms, substr);
    int low_match = lowest_match(terms, nterms, substr);

    *n_answer = high_match - low_match;
    printf("%d\n", *n_answer);
    *answer = (term *)malloc(sizeof(term)*(*n_answer));

    memcpy(*answer, terms+(*n_answer), sizeof(term)*(*n_answer));

    qsort(*answer, *n_answer, sizeof(term), compare_answers);

}
