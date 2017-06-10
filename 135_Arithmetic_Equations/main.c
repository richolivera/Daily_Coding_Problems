#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OPERANDS 4
//#define NUM_OPERATORS 3

typedef enum
{
	ADDITION = 0,
	SUBTRACTION,
	MULTIPLICATION,
	NUM_OPERATORS   //Must always be last entry of enum
}operator_t;

void deleteIntArrayEntry(int * array, int numElements, int location )
{
	int i = 0;
	for(i = location; (i+1) < numElements; i++)
	{
        *(array + i) = *(array + i +1);
	}

}

int solveEquation(const int * const operandArray, const int numOperands, const operator_t * const operatorArray)
{
    int operandsRemaining = numOperands;
	int operatorsRemaining = numOperands - 1;
	int operands[numOperands];
    operator_t operators[numOperands -1];
	int i = 0;
	//Populate local operand array
	for(i = 0; i < numOperands; i++)
	{
		operands[i] = *(operandArray + i);
	}
	//Populate local operator array
	for(i = 0; i < (numOperands - 1); i++)
	{
		operators[i] = *(operatorArray + i);
	}
	//seek and solve Multiplications Left to Right
	for(i = 0; i < operatorsRemaining; i++)
	{
		if(MULTIPLICATION == operators[i])
		{
            operands[i] = operands[i] * operands[i+1];
			//delete array locations
			deleteIntArrayEntry((int *)&operators[0], operatorsRemaining, i); //I think i can cast enum to int
			deleteIntArrayEntry(&operands[0], operandsRemaining, i+1);
			operatorsRemaining--;
			operandsRemaining--;
			i--;
		}
	}
	//solve remaining additions and subtractions Left to Right
	for(i = 0; i < operatorsRemaining; i++)
	{
		if(ADDITION == operators[i])
		{
            operands[i] = operands[i] + operands[i+1];
			//delete array locations
			deleteIntArrayEntry((int *)&operators[0], operatorsRemaining, i); //I think i can cast enum to int
			deleteIntArrayEntry(&operands[0], operandsRemaining, i+1);
			operatorsRemaining--;
			operandsRemaining--;
			i--;
		}
		else //SUBTRACTION == operators[i]
		{
            operands[i] = operands[i] - operands[i+1];
			//delete array locations
			deleteIntArrayEntry((int *)&operators[0], operatorsRemaining, i); //I think i can cast enum to int
			deleteIntArrayEntry(&operands[0], operandsRemaining, i+1);
			operatorsRemaining--;
			operandsRemaining--;
			i--;
		}
	}
    return operands[0];
}

int main (int argc, char * argv[])
{
	int hiInput;
	int loInput;
	int inputRange;
	int operands[4];
	operator_t operators[3];
	int i = 0;
	int result = 0;
	char userInput[160];
	int userResult = result - 1;
	//Take Input Range
	printf("Please Provide Interger Range (Two Intergers separated by a space)\n");
	scanf("%d %d", &loInput, &hiInput);
	inputRange = abs((hiInput + 1) - loInput);
    
	//seed random numbers
	srand(time(NULL));
	
	while(1)
	{
		//Generate 4 Operands
		for(i = 0; i < NUM_OPERANDS ; i++)
		{
			operands[i] = rand() % inputRange + loInput;
		}
		//Generate 3 Operators
		for(i = 0; i < NUM_OPERATORS; i++)
		{
			operators[i] = rand() % NUM_OPERATORS;
		}
		//Solve Problem
		result = solveEquation(&operands[0], NUM_OPERANDS, &operators[0]);
		//printf("result = %i\n",result);
		//printf("operands = %i, %i, %i, %i \n",operands[0],operands[1],operands[2], operands[3]);
		//printf("operators = %i, %i, %i \n",operators[0],operators[1],operators[2]);
		//Print Problem
		for(i = 0; i < NUM_OPERANDS; i++)
		{
			if(i < (NUM_OPERANDS - 1))
			{
				if(ADDITION == operators[i])
				{
					printf("%i + ", operands[i]);
				}
				else if(SUBTRACTION == operators[i])
				{
					printf("%i - ", operands[i]);
				}
				else // (MULTIPLICATION == operands[i])
				{
					printf("%i * ", operands[i]);
				}
			}
			else
			{
				printf("%i\n",operands[i]);
			}
		}
		//Take input and Interpret
		scanf("%s", &userInput[0]);
		if(('q' == userInput[0]) || ('Q'== userInput[0]))
		{
			printf("Goodbye!\n");
			return 0;
		}
		userResult = (int)strtol(&userInput[0], NULL, 10);
		//Report Result
		while(userResult != result)
		{
			printf("Try Again...\n");
			scanf("%s", &userInput[0]);
			if(('q' == userInput[0]) || ('Q'== userInput[0]))
			{
				return 0;
			}
			userResult = (int)strtol(&userInput[0], NULL, 10);
		}
		printf("Correct!\n");
	}
	return 0;
}
