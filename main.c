#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    struct term *terms;
    struct term *answer = NULL;
    int nterms;
    int n_answer;
    int i;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <data-file> <prefix>\n", argv[0]);
        return 1;
    }

    read_in_terms(&terms, &nterms, argv[1]);
    autocomplete(&answer, &n_answer, terms, nterms, argv[2]);

    for (i = 0; i < n_answer; i++)
    {
        printf("%.0lf %s\n", answer[i].weight, answer[i].term);
    }

    free(terms);
    free(answer);
    return 0;
}

