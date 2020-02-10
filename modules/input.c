
#include"input.h"



int promptForInputString(char * prompt, char * inputStr
		, int maxInputSz)
{
    int promptSz = (NULL != prompt) ? strlen(prompt) : 0 ;
	int c = 0;
    char tempPrompt[MAX_STRING_LENGTH] = "Please Input String:";
    if(NULL == prompt)
    {
        prompt = &tempPrompt[0];      
    }
    printf("%s", prompt);
    fgets(inputStr, (maxInputSz+1), stdin); /* add 1 to maxInputsz for '/0'*/
	//fflush(stdin);/* if max character is reached, chars left must be flushed*/
	/* if max character is reached, remaining chars must be flushed*/
	if (maxInputSz == strlen(inputStr))
	{
		while((c=getchar())!='\n' && c != EOF);
	}
    return 0;
}

int promptForInputInt(char * prompt, long int * inputInt)
{
    char tempReceivedStr[MAX_STRING_LENGTH] = {'\0'};
    char tempArr[MAX_STRING_LENGTH] = "Please Input Integer:";
	int sz = 0;
	if(NULL != prompt)
	{
		sz = strlen(prompt);
		if(MAX_STRING_LENGTH < sz)
		{
			sz = MAX_STRING_LENGTH;
		}
		strncpy(&tempArr[0], prompt, sz);
	}
    promptForInputString(&tempArr[0], &tempReceivedStr[0], MAX_STRING_LENGTH);
    /* remove any trailing newline chars */
    tempReceivedStr[strcspn(tempReceivedStr,"\r\n")] = '\0';
    *inputInt = strtol(&tempReceivedStr[0] ,NULL, 10);
    return 0;
}

//main function used for test purposes only
/*
int main()
{
    // this function was written for test purposes only
    char inputArr[MAX_STRING_LENGTH];
    long int * inInt = malloc(sizeof(long int));
    //char promptArr[MAX_STRING_LENGTH] = "Hit me with a string :";
    //char * promptArr = NULL;
  
    //printf("prompt is: %s \n size is: %i \n", promptArr, pSz);
    //promptForInputString(promptArr, inputArr, sizeof(inputArr));
    promptForInputInt(NULL, inInt );
    printf("The int is: %li \n", *inInt);
    free(inInt);
    return 0;
}
*/
