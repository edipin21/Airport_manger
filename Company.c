#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"
#define SIZE_OF_DATE 11
void	initCompany(Company* pComp)
{
    initList(&pComp->DateOfFlightList);
    
    printf("-----------  Init Airline Company\n");
    pComp->name = getStrExactName("Enter company name");
    pComp->flightArr = NULL;
    pComp->flightCount = 0;
}

int	addFlight(Company* pComp,const AirportManager* pManager)
{
     Node* pNode=&pComp->DateOfFlightList.head;
    if (pManager->count < 2)
    {
        printf("There are not enoght airport to set a flight\n");
        return 0;
    }
    pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount+1) * sizeof(Flight*));
    if (!pComp->flightArr)
        return 0;
    pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1,sizeof(Flight));
    if (!pComp->flightArr[pComp->flightCount])
        return 0;
    
    initFlight(pComp->flightArr[pComp->flightCount],pManager);
    char* date=convertDateToChar(&(pComp->flightArr[pComp->flightCount]->date));
    pNode=listInsert(pNode, date);
    pComp->flightCount++;
    return 1;
}

void printCompany(const Company* pComp)
{
    printf("Company %s:\n", pComp->name);
    printf("Has %d flights\n",pComp->flightCount);
    printf("Date of flight are :\n");
    printList(&(pComp->DateOfFlightList.head), printDateOfFlight);
    printFlightArr(pComp->flightArr, pComp->flightCount);
}

void	printFlightsCount(const Company* pComp)
{
    char codeOrigin[CODE_LENGTH+1];
    char codeDestination[CODE_LENGTH + 1];
    
    if (pComp->flightCount == 0)
    {
        printf("No flight to search\n");
        return;
    }
    
    printf("Origin Airport\n");
    getAirportCode(codeOrigin);
    printf("Destination Airport\n");
    getAirportCode(codeDestination);
    
    int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
    if (count != 0)
        printf("There are %d flights ", count);
    else
        printf("There are No flights ");
    
    printf("from %s to %s\n",codeOrigin, codeDestination);
}



void	printFlightArr(Flight** pFlight, int size)
{
    for (int i = 0; i < size; i++)
    printFlight(pFlight[i]);
    
    
}

void	freeFlightArr(Flight** arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        freeFlight(arr[i]);
    }
}

void	freeCompany(Company* pComp)
{
    freeFlightArr(pComp->flightArr, pComp->flightCount);
    free(pComp->flightArr);
    free(pComp->name);
}

char* convertDateToChar(Date* pDate){
    char date[SIZE_OF_DATE];
    char tempDay[3];
    char tempMonth[3];
    char tempYear[5];
    int day=(pDate->day);
    int month=(pDate->month);
    int year=(pDate->year);
    
    if (day<10) {
        strcat(date, "0");
    }
    sprintf(tempDay, "%d", day);
    strcat(date, tempDay);
    strcat(date, "/");
    if (month<10) {
        strcat(date, "0");
    }
    sprintf(tempMonth, "%d", month);
    strcat(date, tempMonth);
    strcat(date, "/");
    sprintf(tempYear, "%d", year);
    strcat(date, tempYear);
    
    
    return date;
}

void printDateOfFlight(const void* p){
    char* date=(char*)p;
    
    printf("%s\n",date);
    
}
