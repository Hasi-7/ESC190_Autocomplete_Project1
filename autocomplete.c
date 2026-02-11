#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(struct term *term1, struct term *term2)
{
    return strcmp(term1->term, term2->term);
}

void read_in_terms(struct term **terms, int *pnterms, char *filename)
{
    *terms = (term *)malloc(sizeof(term)*(*pnterms));
    char line[200];
    FILE *fp = fopen(filename, "r"); 
    for(int i = 0; i < *pnterms; i++)
    { 
        fgets(line, sizeof(line), fp);
        (*terms + i)->weight = atoi(line);
        
        const char delimiter[2] = "\t";
        char *token;
        token = strtok(line, delimiter);
        printf("Line: %s\n", token);
        while (token != NULL) {
            token = strtok(NULL, delimiter);
        }
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
