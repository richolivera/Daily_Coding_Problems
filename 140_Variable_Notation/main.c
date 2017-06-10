#include <stdio.h>
#include <stdlib.h>

int isLower(char x)
{
	if((x >= 0x61) && (x <= 0x7a))
		return 1;
	else
		return 0;
}

int isUpper(char x)
{
	if((x >= 0x41) && (x <= 0x5a))
		return 1;
	else
		return 0;
}

char makeUpperCase(char * goingUp)
{
	if(isLower(*goingUp))
        *goingUp = *goingUp - 0x20;
	return *goingUp;
}

char makeLowerCase(char * goingDown)
{
	if(isUpper(*goingDown))
        *goingDown = *goingDown + 0x20;
	return *goingDown;
}

void printCamelCase(char * str, int strSize)
{
	int i;
	int capitalizeNextChar = 1;
	for(i = 0; (i<strSize && *(str+i)!='\0' && *(str+i)!='\n'); i++)
	{
		if(isUpper(*(str+i)) || isLower(*(str+i)))
		{
			if(capitalizeNextChar==1)
			{
				printf("%c",makeUpperCase(str+i));
				capitalizeNextChar = 0;
			}
			else
			{
				printf("%c",makeLowerCase(str+i));
			}
		}
		else if(*(str+i) == ' ')
		{
            capitalizeNextChar = 1;
		}
	}
	printf("\n");
}

void printSnakeCase(char * str, int strSize)
{
	int i;
	for(i = 0; (i<strSize && *(str+i)!='\0' && *(str+i)!='\n'); i++)
	{
		if(isUpper(*(str+i)) || isLower(*(str+i)))
		{
				printf("%c",makeLowerCase(str+i));
		}
		else if(*(str+i) == ' ')
		{
			printf("%c",'_');
		}
	}
	printf("\n");
}

void printCapSnakeCase(char * str, int strSize)
{
	int i;
	for(i = 0; (i<strSize && *(str+i)!='\0' && *(str+i)!='\n'); i++)
	{
		if(isUpper(*(str+i)) || isLower(*(str+i)))
		{
				printf("%c",makeUpperCase(str+i));
		}
		else if(*(str+i) == ' ')
		{
			printf("%c",'_');
		}
	}
	printf("\n");
}

int main (int argc, char ** argv)
{
    char inputString[80];
    int notation_id;
    

    scanf("%d\n", &notation_id);
    gets(&inputString[0]);

	switch(notation_id)
	{
		case 0:
			printCamelCase(&inputString[0], 80);
			break;
		case 1:
			printSnakeCase(&inputString[0], 80);
			break;
		case 2:
			printCapSnakeCase(&inputString[0], 80);
			break;
		default:
			return 0;
			break;
	}
}
