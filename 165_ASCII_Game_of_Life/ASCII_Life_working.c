#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#define MAX_GRID_DIMENSION 100

typedef struct grid
{
    int xDimension;
    int yDimension;
    int ** gridArray;
} grid_t;

typedef struct neighbors
{
    int topIndex;
    int rightIndex;
    int leftIndex;
    int bottomIndex;
}neighbors_t;

void getNeighbors(grid_t * ourGrid, int x, int y, neighbors_t * neighborIndices)
{
    /*calculate top neighor index*/
    if(0 == y)
    {
        neighborIndices->topIndex = ourGrid->yDimension - 1;
    }
    else
    {
        neighborIndices->topIndex = y - 1;
    }
    /*calculate left neighbor index*/
    if(0 == x)
    {
        neighborIndices->leftIndex = ourGrid->xDimension - 1;
    }
    else
    {
        neighborIndices->leftIndex = x - 1;
    }
    /*calculate right neighbor index*/
    if(ourGrid->xDimension - 1 == x)
    {
        neighborIndices->rightIndex = 0;
    }
    else
    {
        neighborIndices->rightIndex = x + 1;
    }
    /*calculate bottom neighbor index*/
    if(ourGrid->yDimension - 1 == y)
    {
        neighborIndices->bottomIndex = 0;
    }
    else
    {
        neighborIndices->bottomIndex = y + 1;
    }
}

int sumNeighbors(grid_t * ourGrid, int x, int y, neighbors_t * neighborIndices)
{
    int sum = 0;
    sum += ourGrid->gridArray[neighborIndices->topIndex][neighborIndices->leftIndex];
    sum += ourGrid->gridArray[neighborIndices->topIndex][x];
    sum += ourGrid->gridArray[neighborIndices->topIndex][neighborIndices->rightIndex];
    sum += ourGrid->gridArray[y][neighborIndices->rightIndex];
    sum += ourGrid->gridArray[y][neighborIndices->leftIndex];
    sum += ourGrid->gridArray[neighborIndices->bottomIndex][neighborIndices->leftIndex];
    sum += ourGrid->gridArray[neighborIndices->bottomIndex][x];
    sum += ourGrid->gridArray[neighborIndices->bottomIndex][neighborIndices->rightIndex];
    return sum;
}

void initializeGridSize(grid_t * ourGrid, int x, int y)
{
    int i = 0;
    ourGrid->xDimension = x;
    ourGrid->yDimension = y;
    ourGrid->gridArray = malloc(y * sizeof(int *));
    for(i = 0; i < y; i++)
    {
        ourGrid->gridArray[i] = malloc(x * sizeof(int));
    }
}

void freeGridArray(grid_t * ourGrid)
{
    int i = 0;
    int j = 0;
    for(j = 0; j < ourGrid->yDimension; j++)
    {
        free(ourGrid->gridArray[j]);
    }
    free(ourGrid->gridArray);
}

void getGridLine(grid_t * ourGrid, int lineNum)
{
    int i;
    char string[MAX_GRID_DIMENSION];
    scanf("%s",&string);
    for(i=0; i< ourGrid->xDimension; i++)
    {
        if('#' == string[i])
        {
            ourGrid->gridArray[lineNum][i] = 1;
        }
        else
        {
            ourGrid->gridArray[lineNum][i] = 0;
        }
    }
}

void getGrid(grid_t * ourGrid)
{
    int i = 0;
    for(i = 0; i < ourGrid->yDimension; i++)
    {
        getGridLine(ourGrid, i);
    }
}

void updateGrid(grid_t * ourGrid, grid_t * nextGrid)
{
    int i = 0;
    int j = 0;
    int sum = 0;
    int ** tempPtr;
    neighbors_t neighborIndices;
    for(j = 0; j < ourGrid->yDimension; j++)
    {
        for(i = 0; i < ourGrid->xDimension; i++)
        {
            getNeighbors(ourGrid, i, j, &neighborIndices);
            sum = sumNeighbors(ourGrid, i, j, &neighborIndices);
            if(sum == 3)
            {
                nextGrid->gridArray[j][i] = 1;
            }
            else if(sum == 2 && 1 == ourGrid->gridArray[j][i])
            {
                nextGrid->gridArray[j][i] = 1;
            }
            else 
            {
                nextGrid->gridArray[j][i] = 0;
            }
        }
    }
    tempPtr = ourGrid->gridArray;
    ourGrid->gridArray = nextGrid->gridArray;
    nextGrid->gridArray = tempPtr;
}

void printGrid(grid_t * ourGrid)
{
    int i = 0;
    int j = 0;
    for(j=0;j<ourGrid->yDimension; j++)
    {
        for(i=0;i<ourGrid->xDimension; i++)
        {
            if(1 == ourGrid->gridArray[j][i])
            {
                printf("#");
            }
            else
            {
                printf(".");
            }
        }
        printf("\n");
    }
}

int main(int argc, char ** argv)
{
    int i = 0;
    int x;
    int y;
    int n;
    grid_t * ourGrid;
    grid_t * nextGrid;
    ourGrid = malloc(sizeof(grid_t));
    nextGrid = malloc(sizeof(grid_t));
    /*take input*/
    scanf("%i %i %i\n", &n, &x, &y);
    /*initialze grid size*/
    int map[y][x];
    initializeGridSize(ourGrid, x, y);
    initializeGridSize(nextGrid, x, y);
    /*take grid input*/
    getGrid(ourGrid);
    /*run iterations of "life"*/
    for(i = 0; i<n; i++)
    {
        updateGrid(ourGrid, nextGrid);
        printf("\n\noutput: \n");
        printGrid(ourGrid);
    }
    /*free grids*/
    freeGridArray(ourGrid);
    freeGridArray(nextGrid);
    free(ourGrid);
    free(nextGrid);
}
