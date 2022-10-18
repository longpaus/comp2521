// Implementation of the Flight DB ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FlightDb.h"
#include "List.h"
#include "Tree.h"


int compareByFlightNum(Record r1, Record r2);

struct flightDb {
    Tree byFlightNum;
};

FlightDb DbNew(void) {
    FlightDb db = malloc(sizeof(*db));
    db ->byFlightNum = TreeNew(compareByFlightNum);
	return db;
}
void DbFree(FlightDb db) {
    TreeFree(db->byFlightNum,true);
    free(db);
}

bool DbInsertRecord(FlightDb db, Record r) {
	return TreeInsert(db ->byFlightNum,r);
}

List DbFindByFlightNumber(FlightDb db, char *flightNumber) {
	return ListNew();
}

List DbFindByDepartureAirportDay(FlightDb db, char *departureAirport, int day) {
	return ListNew();
}

List DbFindBetweenTimes(FlightDb db, int day1, int hour1, int min1, int day2,
                        int hour2, int min2) {
	return ListNew();
}

Record DbFindNextFlight(FlightDb db, char *flightNumber, int day, int hour,
                        int min) {
	return NULL;
}

/*
compare two records r1 and r2.
comparing by flight number then depature day then hour and then minute.
returns 1 if r1 > r2, 0 if r1 == r2 and -1 if r1 < r2.
*/

int compareByFlightNum(Record r1, Record r2) {
	int flightNumCompare =
	    strcmp(RecordGetFlightNumber(r1), RecordGetFlightNumber(r2));
	if (flightNumCompare != 0) {
		return (flightNumCompare > 0) ? 1 : -1;
	}
    if(RecordGetDepartureDay(r1) != RecordGetDepartureDay(r2)){
        return(RecordGetDepartureDay(r1) > RecordGetDepartureDay(r2)) ? 1 : -1;
    }
    if(RecordGetDepartureHour(r1) != RecordGetDepartureHour(r2)){
        return (RecordGetDepartureHour(r1) > RecordGetDepartureHour(r2)) ? 1 : -1;
    }
    if(RecordGetDepartureMinute(r1) != RecordGetDepartureMinute(r2)){
        return (RecordGetDepartureMinute(r1) > RecordGetDepartureMinute(r2)) ? 1 : -1;
    }
    
    return 0;
}
