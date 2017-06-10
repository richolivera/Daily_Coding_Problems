#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SQUARE_GRID_DIMENSION 5

void printSquareIntGrid(const int * const arrStart, const int gridDimension)
{
    int i = 0;
	int j = 0;
	for(i = 0; i < gridDimension; i++)
	{
        for(j=0; j < gridDimension; j++)
		{
            printf(" %d", *(arrStart + ((gridDimension*i)+j)));
		}
		printf("\n");
	}
	return;
}

int main (int argc, char * argv[])
{
    int i=0;
	int j=0;
	int arr[SQUARE_GRID_DIMENSION][SQUARE_GRID_DIMENSION];
	int zeroTotalsAcross[SQUARE_GRID_DIMENSION] = {0};
	int zeroTotalsDown[SQUARE_GRID_DIMENSION] = {0};
	int zeroTotalsDiagDTTL[SQUARE_GRID_DIMENSION*2 - 1] = {0};

	srand(time(NULL));
	//loop through and populate 2 dimensional array with 1s or 0s
	for(i = 0; i < SQUARE_GRID_DIMENSION; i++)
	{
        for(j=0; j < SQUARE_GRID_DIMENSION; j++)
		{
			//populate array loc with either 1 or 0
			arr[i][j] = rand() % 2;
			//if zero, add to zero totals
			if(arr[i][j] <= 0)
			{
                zeroTotalsAcross[i]++;
				zeroTotalsDown[j]++;
				zeroTotalsDiagDTTL[i+j]++;
			}
		}
	}
    //print zero totals
	for(i = 0; i < SQUARE_GRID_DIMENSION; i++)
	{
        printf("i%d zero total: %d\n",i, zeroTotalsAcross[i]);
	}
	for(i = 0; i < (SQUARE_GRID_DIMENSION*2-1); i++)
	{
        printf("i+j = %d zero total: %d\n",i, zeroTotalsDiagDTTL[i]);
	}
	for(j = 0; j < SQUARE_GRID_DIMENSION; j++)
	{
        printf("j%d zero total: %d\n",j, zeroTotalsDown[j]);
	}

	//prompt user
	printf("When ready for 5x5 grid, type enter key\n");
	getchar();
	//print Grid
    printSquareIntGrid(&arr[0][0], SQUARE_GRID_DIMENSION);
	return 0;
}

