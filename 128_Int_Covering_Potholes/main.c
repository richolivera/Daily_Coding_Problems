#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_GRID_SIZE 10
#define TRUE 1
#define FALSE 0

typedef struct vertex{
    uint8_t isMarked:1;
	uint8_t isROrT:1;
	uint8_t isMatched:1;
    uint8_t :5;
    int predecessor;
	int matchedVertex;
	int numEdges;
	int edges[MAX_GRID_SIZE];
} vertex_t;

typedef enum initOperation{
	totalInit,
    partialInit
}initOperation_t;

vertex_t xVertices[MAX_GRID_SIZE];
vertex_t yVertices[MAX_GRID_SIZE];
int numRows,numCols;
int solutionRows[MAX_GRID_SIZE];
int solutionCols[MAX_GRID_SIZE];

void initializeVertexArrays(initOperation_t op)
{
	int i = 0;
	int j = 0;
	for(i = 0; i < MAX_GRID_SIZE; i++)
	{
        xVertices[i].isMarked = FALSE;
        yVertices[i].isMarked = FALSE;
        xVertices[i].isROrT = FALSE;
        yVertices[i].isROrT = FALSE;
		xVertices[i].predecessor = -1;
        yVertices[i].predecessor = -1;     
		if(op == totalInit)
		{
			xVertices[i].isMatched = FALSE;
			yVertices[i].isMatched = FALSE;
			xVertices[i].matchedVertex = -1;
			yVertices[i].matchedVertex = -1;     
			xVertices[i].numEdges = 0;
			yVertices[i].numEdges = 0;
			for(j=0; j<MAX_GRID_SIZE; j++)
			{
				xVertices[i].edges[j] = 0;
				yVertices[i].edges[j] = 0;
			}
		}
	}
}

void addUnmatchedXToR(int gridSize)
{
	int i;
	for(i=0; i<gridSize; i++)
	{
		if(FALSE == xVertices[i].isMatched)
		{
			xVertices[i].isROrT = TRUE;
		}
	}
}

int findNextUnmarkedR(int gridSize)
{
	int i;
	for(i=0; i<gridSize; i++)
	{
		if((TRUE == xVertices[i].isROrT) && (FALSE == xVertices[i].isMarked))
		{
            return i;
		}
	}
	return -1;
}

void addNewAugmentingPath(int currentY)
{
	int tempY = currentY;
	int tempX;
	yVertices[currentY].isMatched = TRUE;
    do
	{
		tempX = yVertices[tempY].predecessor;
		yVertices[tempY].matchedVertex = tempX;
		xVertices[tempX].matchedVertex = tempY;
		tempY = xVertices[tempX].predecessor;
	}while(0 <= tempY);
	xVertices[tempX].isMatched = TRUE;
}

generateOutput(int gridSize)
{
	numRows = 0;
	numCols = 0;
	int i;
    for(i = 0; i < gridSize; i++)
	{
        if(FALSE == xVertices[i].isROrT)
		{
			solutionRows[numRows] = i;
			numRows++;
			printf("Row %d repaired\n", i);
		}
	}
    for(i = 0; i < gridSize; i++)
	{
        if(TRUE == yVertices[i].isROrT)
		{
			solutionCols[numCols] = i;
			numCols++;
			printf("Column %d repaired\n", i);
		}
	}
}

int main (int argc, char * argv[])
{
	int inputArray[MAX_GRID_SIZE][MAX_GRID_SIZE];
	uint32_t inputDimension;
	char inputLine[80];
	char * endPtr;
	int i = 0;
	int j = 0;
	int newMatchCreated = FALSE;
	int isAnalysisComplete = FALSE;
	int currentX = 0;
	int currentY = 0;

    initializeVertexArrays(totalInit);

    /* Take Input */
	gets(&inputLine[0]);
	inputDimension = (int)strtol(&inputLine[0], NULL, 10);
	for(i = 0; i < inputDimension; i++)
	{
		gets(&inputLine[0]);
		endPtr = &inputLine[0];
		for(j = 0; j < inputDimension; j++)
		{
            inputArray[i][j] = (int)strtol(endPtr, &endPtr, 10);
			if(0 >= inputArray[i][j])
			{
                /*Create an egde on each vertex*/
				xVertices[i].edges[xVertices[i].numEdges] = j;
				yVertices[j].edges[xVertices[i].numEdges] = i;
				xVertices[i].numEdges++;
				yVertices[j].numEdges++;
			}
		}
	}
    	
	/* Perform Analysis */
	while(FALSE == isAnalysisComplete)
	{
		addUnmatchedXToR(inputDimension);
		newMatchCreated = FALSE;
		while(FALSE == newMatchCreated)
		{
            currentX = findNextUnmarkedR(inputDimension);
			if(-1 == currentX)
			{
				isAnalysisComplete = TRUE;
				break;
			}
			xVertices[currentX].isMarked = TRUE;
			for(i = 0; i < xVertices[currentX].numEdges; i++)
			{
				currentY = xVertices[currentX].edges[i];
				/*make sure we do not travel down a matched edge*/
				if(yVertices[currentY].matchedVertex != currentX)
				{
					if(FALSE == yVertices[currentY].isROrT)
					{
						yVertices[currentY].predecessor = currentX;
						yVertices[currentY].isROrT = TRUE;
						if(FALSE == yVertices[currentY].isMatched)
						{
							addNewAugmentingPath(currentY);
							newMatchCreated = TRUE;
							break;
						}
						else
						{
							xVertices[yVertices[currentY].matchedVertex]
								.predecessor = currentY;
							xVertices[yVertices[currentY].matchedVertex]
								.isROrT = TRUE;
						}
					}
				}
			}
			if(TRUE == newMatchCreated)
			{
			    initializeVertexArrays(partialInit);
			}
		}
	}
	/* Print output */
	generateOutput(inputDimension);
}

