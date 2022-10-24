// Implementation of the Flight DB ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FlightDb.h"
#include "List.h"
#include "Tree.h"

int compareByFlightNum(Record r1, Record r2);
int compareByDepartAp(Record r1, Record r2);
int compareByDepartTime(Record r1, Record r2);
static int compareTime(int day1, int hour1, int min1, int day2, int hour2,
                       int min2);

struct flightDb {
	Tree byFlightNum;
	Tree byDepartAp;
	Tree byDepartTime;
};

FlightDb DbNew(void) {
	FlightDb db = malloc(sizeof(*db));
	db->byFlightNum = TreeNew(compareByFlightNum);
	db->byDepartAp = TreeNew(compareByDepartAp);
	db->byDepartTime = TreeNew(compareByDepartTime);
	return db;
}
void DbFree(FlightDb db) {
	TreeFree(db->byFlightNum, true);
	TreeFree(db->byDepartAp, false);
	TreeFree(db->byDepartTime, false);
	free(db);
}

bool DbInsertRecord(FlightDb db, Record r) {
	TreeInsert(db->byDepartAp, r);
	TreeInsert(db->byDepartTime, r);
	return TreeInsert(db->byFlightNum, r);
}

List DbFindByFlightNumber(FlightDb db, char *flightNumber) {
	Record low = RecordNew(flightNumber, "", "", 0, 0, 0, 90);
	Record high = RecordNew(flightNumber, "", "", 6, 23, 59, 90);
	List l = TreeSearchBetween(db->byFlightNum, low, high);
	RecordFree(low);
	RecordFree(high);
	return l;
}

List DbFindByDepartureAirportDay(FlightDb db, char *departureAirport, int day) {
	Record low = RecordNew("", departureAirport, "", day, 0, 0, 0);
	Record high = RecordNew("ZZZZZZZZ", departureAirport, "", day, 23, 59, 0);
	List l = TreeSearchBetween(db->byDepartAp, low, high);
	RecordFree(low);
	RecordFree(high);
	return l;
}

List DbFindBetweenTimes(FlightDb db, int day1, int hour1, int min1, int day2,
                        int hour2, int min2) {
	Record low;
	Record high;
	List l;
	if (compareTime(day1, hour1, min1, day2, hour2, min2) > 0) {
		//day1 is in a later week.
		low = RecordNew("", "", "", day1, hour1, min1, 0);
		high = RecordNew("ZZZZZZZZ", "", "", 6, 23, 59, 0);

		l = TreeSearchBetween(db->byDepartTime, low, high);
		RecordFree(low);
		RecordFree(high);
		low = RecordNew("", "", "", 0, 0, 0, 0);
		high = RecordNew("ZZZZZZZZ", "", "", day2, hour2, min2, 0);

		List l2 = TreeSearchBetween(db->byDepartTime, low, high);
		RecordFree(low);
		RecordFree(high);
		ListExtend(l, l2);
		ListFree(l2);
	} else {
		low = RecordNew("", "", "", day1, hour1, min1, 0);
		high = RecordNew("ZZZZZZZZ", "", "", day2, hour2, min2, 0);
		l = TreeSearchBetween(db->byDepartTime, low, high);
		RecordFree(low);
		RecordFree(high);
	}

	return l;
}

Record DbFindNextFlight(FlightDb db, char *flightNumber, int day, int hour,
                        int min) {
	Record dummy = RecordNew(flightNumber, "", "", day, hour, min, 0);
	Record next = TreeNext(db->byFlightNum, dummy);
	if (next == NULL) {
		dummy = RecordNew(flightNumber, "", "", 0, 0, 0, 0);
		next = TreeNext(db->byFlightNum, dummy);
	}
	RecordFree(dummy);
	return next;
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
	int r1Day = RecordGetDepartureDay(r1);
	int r2Day = RecordGetDepartureDay(r2);
	int r1Hour = RecordGetDepartureHour(r1);
	int r2Hour = RecordGetDepartureHour(r2);
	int r1Minute = RecordGetDepartureMinute(r1);
	int r2Minute = RecordGetDepartureMinute(r2);

	return compareTime(r1Day, r1Hour, r1Minute, r2Day, r2Hour, r2Minute);
}

/*
compare two records r1 and r2.
comparing by departure airport then day then hour and then minute then flight number.
returns 1 if r1 > r2, 0 if r1 == r2 and -1 if r1 < r2.
*/
int compareByDepartAp(Record r1, Record r2) {
	int departAp =
	    strcmp(RecordGetDepartureAirport(r1), RecordGetDepartureAirport(r2));
	if (departAp != 0) {
		return (departAp > 0) ? 1 : -1;
	}
	return compareByDepartTime(r1, r2);
}

/*
compare two records r1 and r2.
compare by depart day,hour, minute then by flight number
returns 1 if r1 > r2, 0 if r1 == r2 and -1 if r1 < r2.
*/

int compareByDepartTime(Record r1, Record r2) {
	int r1Day = RecordGetDepartureDay(r1);
	int r2Day = RecordGetDepartureDay(r2);
	int r1Hour = RecordGetDepartureHour(r1);
	int r2Hour = RecordGetDepartureHour(r2);
	int r1Minute = RecordGetDepartureMinute(r1);
	int r2Minute = RecordGetDepartureMinute(r2);
	if (compareTime(r1Day, r1Hour, r1Minute, r2Day, r2Hour, r2Minute) != 0) {
		return compareTime(r1Day, r1Hour, r1Minute, r2Day, r2Hour, r2Minute);
	}
	return strcmp(RecordGetFlightNumber(r1), RecordGetFlightNumber(r2));
}
/*
compare two times by day, hour then minute.
return 1 if time1 > time 2, -1 if time1 < time2 else 0.
*/

static int compareTime(int day1, int hour1, int min1, int day2, int hour2,
                       int min2) {
	if (day1 != day2) {
		return (day1 > day2) ? 1 : -1;
	}
	if (hour1 != hour2) {
		return (hour1 > hour2) ? 1 : -1;
	}
	if (min1 != min2) {
		return (min1 > min2) ? 1 : -1;
	}
	return 0;
}
