#include<stdio.h>
#include"../modules/input.h"

long int fit1(long int crateX,long int crateY,long int boxX,long int boxY)
{
	long int boxesInX;
	long int boxesInY;
	/*Divide x Dimension*/
    boxesInX = crateX/boxX;
	/*Divide y Dimension*/
	boxesInY = crateY/boxY;
	return boxesInX*boxesInY;
}

long int fit2(long int crateX, long int crateY, long int boxX, long int boxY)
{
	long int origOrientationCount = fit1(crateX, crateY, boxX, boxY);
	long int swappedOrientationCount = fit1(crateX, crateY, boxY, boxX);
	if(origOrientationCount >= swappedOrientationCount)
	{
		return origOrientationCount;
	}
	else
	{
		return swappedOrientationCount;
	}	
}

long int fit3Helper(long int crateX,long int crateY, long int crateZ,
		long int boxX,long int boxY,long int boxZ)
{
	long int boxesInX;
	long int boxesInY;
	long int boxesInZ;
	/*Divide x Dimension*/
    boxesInX = crateX/boxX;
	/*Divide y Dimension*/
	boxesInY = crateY/boxY;
	/*Divide z Dimension*/
	boxesInZ = crateZ/boxZ;
	return boxesInX*boxesInY*boxesInZ;
}

long int fit3(long int crateX,long int crateY, long int crateZ,
		long int boxX,long int boxY,long int boxZ)
{
	long int maxBoxes = 0;
	long int currentBoxCount = 0;
	currentBoxCount = fit3Helper(crateX, crateY, crateZ, boxX, boxY, boxZ);
	if(currentBoxCount > maxBoxes) {maxBoxes = currentBoxCount;}
	currentBoxCount = fit3Helper(crateX, crateY, crateZ, boxX, boxZ, boxY);
	if(currentBoxCount > maxBoxes) {maxBoxes = currentBoxCount;}
	currentBoxCount = fit3Helper(crateX, crateY, crateZ, boxY, boxX, boxZ);
	if(currentBoxCount > maxBoxes) {maxBoxes = currentBoxCount;}
	currentBoxCount = fit3Helper(crateX, crateY, crateZ, boxY, boxZ, boxX);
	if(currentBoxCount > maxBoxes) {maxBoxes = currentBoxCount;}
	currentBoxCount = fit3Helper(crateX, crateY, crateZ, boxZ, boxY, boxX);
	if(currentBoxCount > maxBoxes) {maxBoxes = currentBoxCount;}
	currentBoxCount = fit3Helper(crateX, crateY, crateZ, boxZ, boxX, boxY);
	if(currentBoxCount > maxBoxes) {maxBoxes = currentBoxCount;}
	return maxBoxes;

}
int main()
{
	long int dimensionCount=0;
	char rotateEnabled = '\0';
	long int crateX=0;
	long int crateY=0;
	long int crateZ=0;
	long int boxX=0;
	long int boxY=0;
	long int boxZ=0;

	while((dimensionCount != 2) && (dimensionCount != 3))
	{
		/*prompt user for number of dimensions*/
		promptForInputInt("Please input number of dimensions (2 or 3):", 
						&dimensionCount);
		if((dimensionCount < 2) || ( dimensionCount > 3))
		{
			printf("number of dimension must be 2 or 3...\n");
		}
	}
	if(dimensionCount == 2 )
	{
		while(('y' != rotateEnabled ) && ('n' != rotateEnabled) && 
				('N' != rotateEnabled) && ('Y' != rotateEnabled) )
		{	
			/* prompt for rotate enabled */
			promptForInputString("Enable box rotation (y or n)", 
					&rotateEnabled, 1);
			if(('y' != rotateEnabled ) && ('n' != rotateEnabled) && 
					('N' != rotateEnabled) && ('Y' != rotateEnabled) )
			{
				printf("please enter 'y' or 'n'... \n");
			}
		}
	}
	else
	{
		rotateEnabled = 'N';
	}
	promptForInputInt("Enter crate X dimension (positive int):",
			&crateX);	
	promptForInputInt("Enter crate Y dimension (positive int):",
			&crateY);	
	if(3 <= dimensionCount)
	{
		promptForInputInt("Enter crate Z dimension (positive int):",
				&crateZ);	
	}
	promptForInputInt("Enter box x dimension (positive int):",
			&boxX);	
	promptForInputInt("Enter box y dimension (positive int):",
			&boxY);	
	if(3 <= dimensionCount)
	{
		promptForInputInt("Enter crate z dimension (positive int):",
				&boxZ);	
	}

	if((dimensionCount == 2) && 
			((rotateEnabled == 'N')||(rotateEnabled == 'n')))
	{
		printf("fit 1 Algorithm Result %ld boxes \n", fit1(crateX,crateY,boxX,boxY));
	}
		
	else if((dimensionCount == 2) && 
			((rotateEnabled == 'Y')||(rotateEnabled == 'y')))
	{
		printf("fit 1 Algorithm Result %ld boxes \n", fit1(crateX,crateY,boxX,boxY));
		printf("fit 2 Algorithm Result %ld boxes \n", fit2(crateX,crateY,boxX,boxY));
	}
	else
	{
		printf("fit 3 Algorithm Result %ld boxes \n", fit3(crateX,crateY,crateZ,
					boxX,boxY,boxZ));
	}
		
	
}
