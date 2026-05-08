#include "autocomplete.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_terms(struct term **terms, int nterms)
{
    for (int i = 0; i < 1; i++)
    {
        printf("Term: %s\nTerm Weight: %f\n", (*terms + i)->term, (*terms + i)->weight);
    }
}

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");
    // int match1 = lowest_match(terms, nterms, "Kar");
    // if (match1 != -1)
    // {
    //     printf("Term: %s\nTerm Weight: %d\n", (terms + match1)->term, (terms + match1)->weight);
    // }
    // int match2 = highest_match(terms, nterms, "Tor");
    // if (match2 != -1)
    // {
    //     printf("Term: %s\nTerm Weight: %d\n", (terms + match2)->term, (terms + match2)->weight);
    // }
    struct term *answer;
    int n_answer;
    autocomplete(&answer, &n_answer, terms, nterms, "Kar");

    print_terms(&answer, n_answer);
    //free allocated blocks here -- not required for the project, but good practice
    free(terms);
    free(answer);
    return 0;
}

