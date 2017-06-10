#include "strArray.h"

strArray_t * createInputStrArray()
{
    char inputLine[MAX_INPUT_STRING_LENGTH] = {'\0'};
    char termString[MAX_INPUT_STRING_LENGTH] = {'\0'};
    int i = 0;
    int j = 0;
    numTerms = 0;
    char * temp =NULL;
    strArray_t * p_stringArr;
    
    p_stringArr = (strArray_t *) malloc(sizeof(strArray_t));
    //initialize string array
    p_stringArr->numTerms = 0;

    //get line of input
    fgets(&inputLine[0], MAX_INPUT_STRING_LENGTH-1, stdin);

    for(i = 0; (0==i)||(inputLine[i-1] != '/0'); i++)  
    {
        if(' ' != inputline[i])
        {
           termString[j] = inputLine[i]; 
           j++;
        }
        else if((' ' == inputLine[i]) || ('\0' == inputLine[i]) && (0 != j))
        {
            termString[j] = '\0';
            j++; 
            p_stringArr->term[p_stringArr->numTerms] = (char *)malloc((sizeof(char)*j));
            strcpy(p_stringArr->term[p_stringArr->numTerms], &termString[0]);
            p_stringArr->numTerms++;
            j=0;
            memset(&termString[0], '\0', MAX_INPUT_STRING_LENGTH);
        }
    }
    return p_stringArr;
}

// I also need a function to free allocated memory of a strArray
// start by freeing all pointers in term[]
// then free the p_stringArr pointer
