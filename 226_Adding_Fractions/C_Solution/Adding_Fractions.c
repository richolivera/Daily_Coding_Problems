#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define MAX_FRACTIONS 20
#define MAX_FRAC_STRING_SIZE 30

typedef struct fraction{
    char fracString[MAX_FRAC_STRING_SIZE];
    int64_t numerator;
    int64_t denominator;
}fraction_t;

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
            retVal = minMultiple;
            break;
        }
        minMultiple += lowerBaseMultiple;
    }
    return retVal;
}

//Euclidean Algorithm to find the Greatest Common Devisor via recursion
int64_t GreatestCommonFactor(int64_t a, int64_t b)
{
    // Everything divides 0 
    if (a == 0 || b == 0)
       return 0;

    // base case
    if (a == b)
        return a;

    // a is greater
    if (a > b)
        return GreatestCommonFactor(a-b, b);
    return GreatestCommonFactor(a, b-a);
}

int main()
{
    char delim2[2] = "/";
    char * token = NULL;  
    fraction_t fractionArr[MAX_FRACTIONS] = {"", 0 , 0 };
    int numFractions = 0;
    int i = 0;
   
    // Retrieve fractions from user
    printf("Enter number of fractions to add:\n");
    scanf("%i", &numFractions);
    printf("Enter Fractions:\n");
    for(i=0; i < numFractions; i++ )
    {
        //populate the fraction info
        scanf("%s", (fractionArr[i]).fracString);
        (fractionArr[i]).numerator = atoi(strtok((fractionArr[i]).fracString, delim2));
        (fractionArr[i]).denominator = atoi(strtok(NULL , delim2));
    }

    int64_t gcf = 0;
    int64_t lcm = 1;
    int64_t numeratorTotal = 0;

    //loop throught to get the lowest common denominator
    for(i=0; i<numFractions; i++)
    {
       lcm = LowestCommonMultiple(lcm,(fractionArr[i]).denominator);
    }
    printf("lcm = %llu \n", lcm);
    
    //loop through and multiply numerators by lcm/denom. Add to total
    for(i=0; i<numFractions; i++)
    {
        (fractionArr[i]).numerator = (fractionArr[i]).numerator * (lcm/(fractionArr[i]).denominator);
        numeratorTotal += (fractionArr[i]).numerator ;
    }
    
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
