// Implementation of the Flight DB ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FlightDb.h"
#include "List.h"
#include "Tree.h"


int compareByFlightNum(Record r1, Record r2);
int compareByDepartAp(Record r1, Record r2);

struct flightDb {
    Tree byFlightNum;
    Tree byDepartAp;
};

FlightDb DbNew(void) {
    FlightDb db = malloc(sizeof(*db));
    db ->byFlightNum = TreeNew(compareByFlightNum);
    db -> byDepartAp = TreeNew(compareByDepartAp);
	return db;
}
void DbFree(FlightDb db) {
    TreeFree(db->byFlightNum,true);
    TreeFree(db->byDepartAp,false);
    free(db);
}

bool DbInsertRecord(FlightDb db, Record r) {
    TreeInsert(db->byDepartAp,r);
	return TreeInsert(db ->byFlightNum,r);
}

List DbFindByFlightNumber(FlightDb db, char *flightNumber) {
    Record low = RecordNew(flightNumber,"","",0,0,0,90);
    Record high = RecordNew(flightNumber,"","",6,23,59,90);
    List l = TreeSearchBetween(db->byFlightNum,low,high);
    RecordFree(low);
    RecordFree(high);
    return l;
}

List DbFindByDepartureAirportDay(FlightDb db, char *departureAirport, int day) {
    Record low = RecordNew("",departureAirport,"",day,0,0,0);
    Record high = RecordNew("ZZZZZZZZ",departureAirport,"",day,23,59,0);
    List l = TreeSearchBetween(db->byDepartAp,low,high);
    RecordFree(low);
    RecordFree(high);
    return l;
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

/*
compare two records r1 and r2.
comparing by departure airport then day then hour and then minute then flight number.
returns 1 if r1 > r2, 0 if r1 == r2 and -1 if r1 < r2.
*/
int compareByDepartAp(Record r1, Record r2){
    int departAp = strcmp(RecordGetDepartureAirport(r1),RecordGetDepartureAirport(r2));
    if(departAp != 0){
        return (departAp > 0) ? 1 : -1;
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
    int flightNumCompare =
	    strcmp(RecordGetFlightNumber(r1), RecordGetFlightNumber(r2));
	if (flightNumCompare != 0) {
		return (flightNumCompare > 0) ? 1 : -1;
	}
    return 0;

}
