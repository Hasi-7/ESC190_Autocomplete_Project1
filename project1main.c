#include "autocomplete.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//i presume this is where I would test the code...

//another comparison function to put it order of weight

int main(void)
{
    struct term *terms;
    int nterms;

    //manually making a list so I know what to expect
    // term* testing_terms = (term*)malloc(sizeof(term) * 7);
    // strcpy((testing_terms->term), "Apples");
    // testing_terms->weight = 0;
    // strcpy(((testing_terms + 1)->term), "Application");
    // (testing_terms+1)->weight = 2;
    // strcpy(((testing_terms + 2)->term), "Bugbug");
    // (testing_terms + 2)->weight = 1;
    // strcpy(((testing_terms + 3)->term), "Buggies");
    // (testing_terms + 3)->weight = 9;
    // strcpy(((testing_terms + 4)->term), "Bugs");
    // (testing_terms + 4)->weight = 7;
    // strcpy(((testing_terms + 5)->term), "Chariots");
    // strcpy(((testing_terms + 6)->term), "Charts");
    // char* substr = "Bug";
    // int lower = lowest_match(testing_terms, 7, substr);
    // int higher = highest_match(testing_terms, 7, substr);
    // printf("%d, %d\n", lower, higher);

    // int a = compare_weights(testing_terms + 2, testing_terms + 3);
    // printf("%d", a);

    //GIVEN TESTING CODES

    read_in_terms(&terms, &nterms, "cities.txt");
    //int n;
    // for(n = 0; n < 10; n++){
    //     printf("%s\n", (terms + n)->term);
    // }

    //printf("%d\n", nterms);
    lowest_match(terms, nterms, "Tor");
    highest_match(terms, nterms, "Tor");
    
    struct term *answer;
    int n_answer;
    // autocomplete(&answer, &n_answer, testing_terms, 7, "App");
    // printf("%s\n", answer->term); //they just print the first one...?
    // autocomplete(&answer, &n_answer, testing_terms, 7, "Bug"); 
    // printf("%s\n", answer->term); //they just print the first one...?
    autocomplete(&answer, &n_answer, terms, nterms, "Tor");

    
    printf("%s - %f\n", (answer)->term, (answer)->weight);
    
    //free allocated blocks here -- not required for the project, but good practice
    //free(testing_terms);
    free(answer);
    free(terms);
    return 0;
}