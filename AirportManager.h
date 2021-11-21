#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"
#include "General.h"
#include "listGen.h"
typedef struct
{
    List airportList;
	int			count;
}AirportManager;

int	initManager(AirportManager* pManager);
int	addAirport(AirportManager* pManager);
void setAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager,  const char* code);
int	checkUniqeCode(const char* code, const AirportManager* pManager);
void printAirports(const AirportManager *pManager);
void freeManager(void* pManager);
int compareAirportByCode(const void* p1,const void* p2);
#endif
