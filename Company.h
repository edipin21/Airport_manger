#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"
typedef struct
{
	char*name;
	int	flightCount;
	Flight**	flightArr;
    List DateOfFlightList;
    
}Company;

void initCompany(Company* pComp);
int addFlight(Company* pComp,const AirportManager* pManager);
void printCompany(const Company* pComp);
void printFlightsCount(const Company* pComp);
void printFlightArr(Flight** pFlight, int size);
void freeFlightArr(Flight** arr, int size);
void freeCompany(Company* pComp);
char* convertDateToChar(Date* pDate);
void printDateOfFlight(const void* p);
#endif

