#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_STRING_LENGTH 256

void main(int argc, char*argv[])
{
    int N,i,j;
	scanf("%i\n",&N);
	char * strArray[16];
	unsigned int max_string_length=0;
	char current_char;
	//loop to gather input
	for(i = 0; i<N; i++)
	{
		strArray[i] = (char *)malloc((size_t)MAX_STRING_LENGTH);
		gets(strArray[i]);
	    if( strlen(strArray[i]) > max_string_length)	
		{
			max_string_length = strlen(strArray[i]);
		}
	}
    //loop to print output
	for(j=0; j <= max_string_length;j++)
	{
		for(i=0; i < N; i++)
		{
	 	    if(j >= strlen(strArray[i]))
			{
				printf(" ");
			}
			else
			{
				printf("%c",*(strArray[i]+j));
			}
		}
		printf("\n");
	}
    //loop to free pointers
	for(i = 0; i>N; i++)
	{
        free(strArray[i]);
	}
}
