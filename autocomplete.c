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
    *pnterms = 0;
    *terms = (term *)malloc(sizeof(term)*(*pnterms));
    char line[200];
    FILE *fp = fopen(filename, "r"); 
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL)
    { 
        (*terms + i)->weight = atoi(line);
        const char delimiter[2] = "\t";
        char *token;
        token = strtok(line, delimiter);
        while (token != NULL) 
        {
            token = strtok(NULL, delimiter);
        }
        strcpy((*terms + i)->term, token);
        i++;
        
    } 
    fclose(fp);
    qsort(*terms, *pnterms, sizeof(terms), compare);
}

int lowest_match(struct term *terms, int nterms, char *substr)
{
    return 0;
}

int highest_match(struct term *terms, int nterms, char *substr)
{
    return 0;
}

void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr)
{

}
