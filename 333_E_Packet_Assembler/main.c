//Assumptions:
//    1) Max character string length of packet is never more than 100
//    2) duplicate packets will not happen
//

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STR_LEN 100
#define FALSE 0
#define TRUE 1

typedef struct packet{
    char pktStr[MAX_STR_LEN];
}packet_t;

typedef struct message{
    int msgId; 
    int totalPkts;
    int receivedPkts;
    packet_t * msgPkts;
}message_t;


// function: FreeMsg()
void freeMsg(message_t ** msgArr, int msgId, int totalPkts, int * numMsgs)
{
    int i = 0, beyondCompletedMsgIndex = FALSE;
    message_t * newPtr = NULL; 
    if(*numMsgs > 1)
    {
        //malloc smaller space
        newPtr = malloc(sizeof(message_t)*(*numMsgs-1));
        //foreach message
        for(i=0; i<(*numMsgs); i++)
        { 
            if((*msgArr)[i].msgId != msgId)
            {
                //copy over msgs which are not msgId
                newPtr[(i-beyondCompletedMsgIndex)].msgId = (*msgArr)[i].msgId;
                newPtr[(i-beyondCompletedMsgIndex)].totalPkts = (*msgArr)[i].totalPkts;
                newPtr[(i-beyondCompletedMsgIndex)].receivedPkts = (*msgArr)[i].receivedPkts;
                newPtr[(i-beyondCompletedMsgIndex)].msgPkts = (*msgArr)[i].msgPkts;
            }
            else
            {   
                //set boolean to true (1)
                beyondCompletedMsgIndex = TRUE;
                //free msgPkts Pointer
                free((*msgArr)[i].msgPkts);
            }
        }
    }
    else if(*numMsgs == 1)
    {
        free((*msgArr)[0].msgPkts);
    }
    //free original pointer
    free(*msgArr);
    //set original pointer to new pointer
    if(*numMsgs > 1)
    {(*msgArr) = newPtr;}
    else
    {(*msgArr = NULL);}
    //decrement numMsgs
    *numMsgs = *numMsgs-1;
}

// function: AddMsg()
void addMsg(message_t ** msgArr, int msgId, int totalPkts, int * numMsgs )
{
    int i = 0;
    message_t * newPtr=NULL;
    //malloc larger space
    newPtr = malloc(sizeof(message_t)*(1+(*numMsgs)));
    //create new record
    newPtr[(*numMsgs)].msgId = msgId;
    newPtr[(*numMsgs)].totalPkts = totalPkts;
    newPtr[(*numMsgs)].receivedPkts = 0;
    newPtr[(*numMsgs)].msgPkts = malloc(sizeof(packet_t)*totalPkts);
    if(0 < *numMsgs)
    {
        //foreach message
        for(i=0; i<(*numMsgs); i++)
        {
            //copy over fields for each message 
            newPtr[i].msgId = (*msgArr)[i].msgId;
            newPtr[i].totalPkts = (*msgArr)[i].totalPkts;
            newPtr[i].receivedPkts = (*msgArr)[i].receivedPkts;
            newPtr[i].msgPkts = (*msgArr)[i].msgPkts;
        }
        //free original pointer
        free(*msgArr);
    }
    //set original pointer to new pointer
    (*msgArr) = newPtr;
    //increment numMsgs
    *numMsgs = *numMsgs+1;
}

// function: printAndRemoveMsg()
void printAndRemoveMsg(message_t ** msgArr, int msgId, int totalPkts, char * msgStr, int * numMsgs, int msgIndex)
{
    int i = 0;
    //print msg specified in MsgID
    for(i = 0; i<totalPkts; i++)
    {
        printf("%s\n",(*msgArr)[msgIndex].msgPkts[i].pktStr);
    }
    freeMsg(msgArr, msgId, totalPkts, numMsgs);
}

//function: addPktAndCheckCompletion()
void addPktAndCheckCompletion(message_t ** msgArr, int msgId, int pktId, int totalPkts, char * msgStr, int * numMsgs, int msgIndex)
{
    //add Pkt to corresponding pkt array
    strncpy((*msgArr)[msgIndex].msgPkts[pktId].pktStr, msgStr, MAX_STR_LEN);
    //increment received Pkts
    (*msgArr)[msgIndex].receivedPkts++;
    //check for completeion, print if complete
    if((*msgArr)[msgIndex].receivedPkts == (*msgArr)[msgIndex].totalPkts)
    {
        printAndRemoveMsg(msgArr, msgId, totalPkts, msgStr, numMsgs ,msgIndex);
    }
}

// function: ProcessPkt()
void processPkt(message_t ** msgArr, int msgId, int pktId, int totalPkts, char * msgStr, int * numMsgs)
{
    int i=0, isInMsgArr = FALSE, index = 0;
    //loop to determine if pkt is already in msgArr
    for(i=0; i<(*numMsgs); i++)
    {
        if((*msgArr)[i].msgId == msgId)
        {
            index = i;
            isInMsgArr = TRUE;
            break;
        }
    }
    if(TRUE == isInMsgArr)
    {    
        addPktAndCheckCompletion(msgArr, msgId, pktId, totalPkts, msgStr, numMsgs, i);
    }
    else
    { 
        addMsg(msgArr, msgId, totalPkts, numMsgs); //this call increments numMsgs value
        addPktAndCheckCompletion(msgArr, msgId, pktId, totalPkts, msgStr, numMsgs, (*numMsgs)-1);
    }
}


int main()
{
    int x=0, y=0, z=0, numMsgs=0;
    char str[MAX_STR_LEN] = {0};
    char tmpStr[MAX_STR_LEN] = {0};
    message_t * msgArr=NULL;
    printf("Enter input ('Ctrl-D' terminates input):\n");
    do
    {
        fgets(str,MAX_STR_LEN,stdin);
        if(str[strlen(str)-1]=='\n'){str[strlen(str)-1]='\0';}
        strncpy(tmpStr, &str[0], 5);
        x = atoi(tmpStr);
        strncpy(tmpStr, &str[8], 3);
        y = atoi(tmpStr);
        strncpy(tmpStr, &str[12], 3);
        z = atoi(tmpStr);
        processPkt(&msgArr,x,y,z,&str[0],&numMsgs);
        //printf("x = %i, y = %i, z = %i, strg = %s \n", x,y,z,strg);
    }while(!feof(stdin));
}
