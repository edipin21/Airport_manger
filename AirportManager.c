#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AirportManager.h"

int	initManager(AirportManager* pManager)
{
    Airport *temp = NULL;
    initList(&pManager->airportList);
    Node *pNode=&pManager->airportList.head;
    
    printf("-----------  Init airport Manager\n");
    pManager->count = 0;
    
    
    int count=0;
    do {
        printf("How many airport?\t");
        scanf("%d", &count);
    } while (count < 0);
    //clean buffer
    char tav;
    scanf("%c", &tav);
    if (count == 0)
        return 1;
    
    
    
    
    for (int i = 0; i < count; i++)
    {
        temp=(Airport*)malloc(sizeof(Airport));
        if(!temp)
            return 0;
        setAirport(temp, pManager);
        pNode= findPlaceToInsert(&pManager->airportList.head, temp->code, compareAirportByCode);
        listInsert(pNode, temp);
        
        pManager->count++;
    }
    free(temp);
    return 1;
}

int	addAirport(AirportManager* pManager)
{
    Node*tempNode=(Node*)malloc(sizeof(Node));
    Airport* pPort=(Airport*)malloc(sizeof(Airport));
    if(!pPort)
        return 0;
    setAirport(pPort, pManager);
    tempNode=&pManager->airportList.head;
    for (int i=0; i<pManager->count; i++) {
        tempNode=tempNode->next;
    }
    listInsert(tempNode, pPort);
    pManager->count++;
    return 1;
}

void  setAirport(Airport* pPort, AirportManager* pManager)
{
    while (1)
    {
        getAirportCode(pPort->code);
        if (checkUniqeCode(pPort->code, pManager))
            break;
        
        printf("This code already in use - enter a different code\n");
    }
    
    initAirportNoCode(pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
    Airport *tempPort;
    
    tempPort=(Airport*)malloc(sizeof(Airport));
    strcpy(tempPort->code, code);
    
    Node*tempNode=L_find(pManager->airportList.head.next, tempPort, isSameAirport);
    if (tempNode!=NULL) {
        free(tempPort);
        return  tempNode->data;
    }
    free(tempPort);
    return NULL;
    
}

int checkUniqeCode(const char* code,const AirportManager* pManager)
{
    Airport* port = findAirportByCode(pManager, code);
    
    if (port != NULL)
        return 0;
    
    return 1;
}

int compareAirportByCode(const void* p1,const void* p2){
    const Airport* pPort1=(const Airport*)p1;
    const char* Port2Code=(const char*)p2;
    
    if (strcmp(pPort1->code, Port2Code)>0) {
        return 1;
    }
    return -1;
}





void printAirports(const AirportManager *pManager)
{
    
    printList((List*)pManager->airportList.head.next, printAirport);
    printf("\n");
    
}

void freeManager(void* pManager){
    
    free(pManager);
}
