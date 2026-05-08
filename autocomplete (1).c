//Project1: Autocomplete
//Code by Shirleen Chan 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "autocomplete.h"
//note for self: Run the code in ECF or gradescope with valgrind before officially submitting the code in Gradescope;
//There is a 2.5% deduction from memory leaks
//we are also working with a struct "term" with char[200] and a double for weight

//about valgrind into gradescope
//submit the entire project (including header files, function files, and main
//it will takes a while
//it will just dump the valgrind output (not very smooth in comparision to installing but hey it works!!)

//HELPER FUNCTIONS
//make a comparing string, because qsort is not smart enough to do everything for me
//strcmp() returns a negative number if the first argument comes before the second argument,
//and positive number if the first argument comes after the second argument
int compare_strings(const void* term1, const void* term2){
    return strcmp(((term*)term1)->term, ((term*)term2)->term);
}

//another comparison function to put it order of weight
int compare_weights(const void* term1, const void* term2){
    //negative if the term1 goes before (meaning bigger weight)
    //positive if term1 goes after (meaning smaller weight)
    int weight1 = ((term*)term1)->weight; 
    int weight2 = ((term*)term2)->weight;
    return weight2 - weight1;
    //if term1's weight is bigger than that of term2, then the different would be negative
}

//find the location of the Tab
int find_da_tab(char* line){
    int i;
    int len = strlen(line);
    for(i = 0; i < len; i++){
        if(*(line + i) == '\t'){
            return i;
        }
    }
    return strlen(line); //failsafe
}

//remove the return at the end of the string 
void remove_return(char* line){
    int len = strlen(line);
    line[len-1] = '\0'; //go to the location of the return (which is the last character)
    //and replace it with a null
}

//this code: Valgrind is saying that I am trying to move things into things that don exist or smt like that 
void read_in_terms(struct term **terms, int *pnterms, char *filename){
    //read file, add words and weights into file, then sort it using qsort in alphabetical order

    //initialize
    char* local_term;
    int index_of_tab;

    //first line is the number of lines in the file
    char line[200];
    FILE *fp = fopen(filename, "r");

    //read the first line and get the number of terms within the file
    //which is the only thing on the first line anyway
    fgets(line, sizeof(line), fp);
    *pnterms = atoi(line); //store this number in the address

    //then i make a malloc
    *terms = (term*)malloc(sizeof(term) * (*(pnterms)));

    //loop through each word...what a pain in the ass
    for(int i = 0; i < *(pnterms); i++) //we already read one line, so nterms-1 is the upper limit
    {
        fgets(line, sizeof(line), fp); //get the line
        //why do they not let you get the line

        //since we don't really know like how long each of the strings would be 
        //that would mean that we will actually need to find a way to extract just the word
        //of the line
        remove_return(line);
        index_of_tab = find_da_tab(line);
        local_term = line + index_of_tab + 1;
        //eg if the line is 123a, the index is 3 where a is located, so when we splice it
        //we would have 0 (line) + 3 (location of a, as our first address for the string 

        //then I store it on the struct?
        strcpy((*terms+i)->term, local_term);
        //since you are suppose to place a string inside, use * for the second parameter?
        //store the weight as well
        //((*terms)+i)->weight = atof(line);
        (*terms)[i].weight = atof(line);
        
    }
    fclose(fp);

    //then we sort through it...using qsort
    //usually qsort is for arrays but since mallocs acts very similar to arrays
    //it would probably work
    //qsort(char* arr, int number_of_terms, int size_per_element, comparison_function)
    qsort(*terms, *pnterms, sizeof(term), compare_strings);
    //they do not like my compare_strings function and they don let me use it...
    //it should be sorted now...
}

//the next two function is for the binary search
//must be done in O(log(n)) -> it must be the divide thing or else it would probably not have 
//the run time complexiy of that
int lowest_match(struct term *terms, int nterms, char *substr){
    //function returns the index of the first term in a lexicographical order list with beginnning that matches 
    //the string substr 

    //initialize
    int left = 0;
    int right = nterms - 1; //indices starts at 0 and has n terms and thus the last indice must be
    //nterms - 1
    int mid;
    char mid_string[200]; //the same amount of characters a term in the struct can have
    int len_substr = strlen(substr); //get the length of the string

    while(left<=right){
        //get the middle index
        mid = (left + right)/2; //integer division is the norm in C, and it rounds
        //towards zero
         
        strcpy(mid_string, (terms + mid)->term);
        //copy the string of the term list into the local middle string find the middle string 
        //then I will add a null at the location where the string to get the beginning of the string
        //since mid_string is initialized as an array maybe I can just 
        mid_string[len_substr] = '\0'; 

        //then I would compare the beginning and use the same mechanism as the binary
        //search from the lab to move the boundaries
        if(strcmp(mid_string, substr)<0){
            //by the given assumption the mid_string would come before the substr
            //this is the same as from L[mid] < target, the number L[mid] would come before the 
            //target (which is substring for us)
            left = mid + 1;
        }
        else{
            right = mid -1;
        }
    }
    return left;
}

int highest_match(struct term *terms, int nterms, char *substr){
    //function returns the index of the last term in a lexicographical order list with beginning that matches
    //the string substr

    //initialize
    int left = 0;
    int right = nterms - 1; 
    int mid;
    char mid_string[200]; 
    int len_substr = strlen(substr);

    while(left<=right){
        //get the middle index
        mid = (left + right)/2; 
         
        //copy the string + edit
        strcpy(mid_string, (terms + mid)->term);
        mid_string[len_substr] = '\0'; 

        //comparison
        if(strcmp(mid_string, substr)>0){
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    //return the right index
    return right;
}


//this code has memory leaks 
void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){

    //find the left and right of the term
    int left; 
    int right;
    left = lowest_match(terms, nterms, substr);
    right = highest_match(terms, nterms, substr);
    //the number of answers would be right - left + 1 (including both of them)
    *n_answer = right - left + 1; //store it in the address

    //make a new malloc for answer
    *(answer) = (term*)malloc(sizeof(term)*(*n_answer));
    //copy the terms within the range into this malloc
    int i;

    //copy the strings into each of the slots
    for(i = 0; i < (*n_answer); i++){
        //since we are including the last one and we start at zero we add a _1
        strcpy(((*answer) + i)->term, (terms + left + i)->term);
        ((*answer) + i)->weight = ((terms) + left + i)->weight;
        //strcpy the two...
    }
    
    //then sort this answer and get the address for the first one. 
    qsort(*answer, *n_answer, sizeof(term), compare_weights);
    //this one is legit not working for some reason even though like...the first one worked?

}




