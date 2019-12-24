#include<stdio.h>
#include<math.h>
#include "../modules/input.h"

int main()
{
    long int * userInputInt = malloc(sizeof(long int));
    long int workingNum = 0;    
    long int outNum = 0;
    int outPlaceCounter=0;
    int inPlaceCounter=0;
	//printf("Hello, world\n");
	/*prompt user for integer*/
    promptForInputInt("Please provide number: ", userInputInt);
    workingNum = *userInputInt;
    while(0 != workingNum/((int)pow(10,inPlaceCounter)))
    {
	/*extract the digit we care about in this iteration*/
	workingNum = ((*userInputInt)%((int)pow(10,(inPlaceCounter+1)))) / 
	             ((int)pow(10,inPlaceCounter));
        if(9 == workingNum)
	{ 
	    /*if digit is 9, first add 10*10^outPlaceCounter, then 
	     * increment outPlaceCounter by 2*/
	    outNum += (int)pow(10,(outPlaceCounter+1));
	    outPlaceCounter += 2;
	}	
	else
	{
	    /*if digit is not 9, first add (digit +1)*10^outPlaceCounter, then
	     increment outPlaceCounter by 1 */
	    outNum += (workingNum +1)*(int)pow(10,(outPlaceCounter));
	    outPlaceCounter++;
	}
	/*prep for next loop interation*/    
	workingNum = *userInputInt;
	inPlaceCounter++;
    }

    printf("Output Number: %li \n", outNum);
    free(userInputInt);
    return 0;
}

