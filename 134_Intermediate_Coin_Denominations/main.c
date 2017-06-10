    #include <stdio.h>
    #include <stdlib.h>

    typedef struct coin
    {
        int quantity;
        int value;
    }coin_t;

    int printDenoms(int sum, coin_t * arr, int index)
    {
        int base;
        int rem = 0;
        int i;
        if(0 == index)
        {
            arr->quantity = sum/(arr->value);
            for(i=0; i<50; i++)
            {
                if(0 < (arr+i)->quantity )
                {
                    printf("%d:%d ",(arr+i)->value, (arr+i)->quantity);
                    rem = 1;
                }
            }
            if(1 == rem)
            {
                printf("\n");
                rem = 0;
            }
        }
        else if(sum < (arr+index)->value)
        {
            printDenoms(sum, arr, index-1);
        }
        else
        {
            /* find base */
            base = sum/((arr+index)->value);
            i = 0;
            while(i<=base)
            {
                /* calculate remander */
                rem = sum - (((arr+index)->value)* i);

                /* note current coin quantity */
                (arr+index)->quantity = i;

                /* handle remainder */
                printDenoms(rem, arr, index - 1);
                i++;
            }
        }
        return 0;
    }

    int main (int argc, char * argv[])
    {
        char inputString[80] = {'\n'};
        char * pEnd;
        int numDenominations;
        int sum;
        coin_t denominations[10][50];
        int denomSize[10] = {0};
        int i;
        int j =-1;

        /* initialize coin array */
        memset(&denominations[0][0], 0, (sizeof(coin_t)*500));

        gets(&inputString[0]);
        numDenominations = strtol(&inputString[0], &pEnd, 10);
        sum = strtol(pEnd, NULL, 10);

        if(numDenominations > 10)
        {
            printf("Too many denominations \n");
            return 0;
        }

        /* acquire input */
        for(i= 0; i < numDenominations; i++)
        {
            gets(&inputString[0]);
            pEnd = &inputString[0];
            while(0 != j)
            {
                j = strtol(pEnd, &pEnd, 10);
                if (0 != j)
                {
                    denominations[i][denomSize[i]].value = j;
                    denomSize[i]++;
                }
            }
            j=-1;
        }

        /* print output */
        for(i= 0; i < numDenominations; i++)
        {
            printf("Currency %d Combinations: \n", i+1); 
            printDenoms(sum, &denominations[i][0], denomSize[i]-1);
        }
        return 0;
    }
