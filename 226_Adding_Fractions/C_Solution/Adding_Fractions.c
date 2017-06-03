#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define MAX_FRACTIONS 20

char input[500] = "1/7,35/192,61/124,90/31,5/168,31/51,69/179,32/5,15/188,10/17";

int64_t LowestCommonMultiple( int64_t n1, int64_t  n2)
{
    int64_t minMultiple, retVal, lowerBaseMultiple;
    
    //Prevent division by 0
    n1 = (n1 == 0) ? 1 : n1;
    n2 = (n2 == 0) ? 1 : n2;

    // maximum number between n1 and n2 is stored in minMultiple
    lowerBaseMultiple = (n1>n2) ? n1 : n2;
    minMultiple = lowerBaseMultiple;

    // Always true
    while(1)
    {
        if( minMultiple%n1==0 && minMultiple%n2==0 )
        {
            //printf("The LCM of %d and %d is %d.", n1, n2,minMultiple);
            retVal = minMultiple;
            break;
        }
        minMultiple += lowerBaseMultiple;
    }
    return retVal;
}

int64_t GreatestCommonFactor(int64_t n1, int64_t n2)
{
    int64_t maxFactor, lowerBaseValue;  
    int64_t retVal = 1;
    maxFactor = (n1>n2) ? n1 : n2;
    lowerBaseValue =  (n1>n2) ? n2 : n1;

    // Always true
    while(0 < maxFactor)
    {
        if( n1%maxFactor==0 && n2%maxFactor==0 )
        {
            //printf("The LCM of %d and %d is %d.", n1, n2,minMultiple);
            retVal = maxFactor;
            break;
        }
        maxFactor -= lowerBaseValue;
    }
    return retVal;
    
}

int main()
{
    char delim[2] = ",";
    char delim2[2] = "/";
    char * token = NULL;  
    char * fractionArr[MAX_FRACTIONS] = {NULL};
    int i = 0;
    int64_t numeratorArr[MAX_FRACTIONS] = {0};
    int64_t denomArr[MAX_FRACTIONS] = {0};
    
    //populate the denominator arrary
    //get first token
    token = strtok( input, delim);
    //loop through fractions
    while(token != NULL)
    {
        //add to the fraction array
        fractionArr[i] = token; 
        //get the next token
        //printf("fractionArr index %i : %s\n", i, fractionArr[i] );
        token = strtok( NULL, delim);
        i++;

    }
    i = 0;
    //loop through fractions to populate numerator and denominator array
    while(fractionArr[i] != NULL)
    {
       //capture Numerator
       token = strtok(fractionArr[i], delim2);
       numeratorArr[i] = atoi(token);
       //capture Denominator
       token = strtok( NULL, delim2);
       denomArr[i] = (token == NULL) ? 1 : atoi(token);

       //printf("numeratorArr index %i : %i\n", i, numeratorArr[i] );
       //printf("denomArr index %i : %i\n", i, denomArr[i] );
       i++;
    }
    

    int64_t denomArrSize =  (sizeof(denomArr)/sizeof(denomArr[0]));
    int64_t gcf = 0;
    int64_t lcm = 1;
    int64_t numeratorTotal = 0;

    //loop throught to get the lowest common denominator
    for(i=0; i<denomArrSize; i++)
    {
       lcm = LowestCommonMultiple(lcm, denomArr[i]);
       // printf("index [%i] lcm = %lli\n", i, lcm);
    }
    //printf("lcm = %i\n", lcm);
    
    //loop through and multiply numerators by lcm/denom. Add to total
    for(i=0; i<denomArrSize; i++)
    {
      if(0 != denomArr[i])
      {
        numeratorArr[i] = numeratorArr[i] * (lcm/denomArr[i]);
        numeratorTotal += numeratorArr[i];
      }
    }
    //printf("numeratorTotal = %lli\n", numeratorTotal);
    
    // reduce the fraction by repeatedly dividing by the greatest common factor
    while(1 != gcf )
    {
        gcf = GreatestCommonFactor(lcm, numeratorTotal);
        numeratorTotal = numeratorTotal/gcf;
        lcm = lcm/gcf;
    }
    printf("answer: %lli/%lli\n", numeratorTotal, lcm);

    return 0;
}
