#include "event.h"
#ifndef _date_h
#define _date_h
#define NUMBER_OF_DAYS 7

enum days { SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
char *daysOfAWeek[] = { "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY" };

typedef struct _Date {
	unsigned int numberOfEvents;
	Event **events;
} Date;

// calculates whether a given day of a month is a working day or not, takes 3 args startDay, working days, current day
int isWorkingDay(int, int *, int);

// converts time + duration to time, ex - 1050 + 11 => 1101 (24 hr format), takes in time, duration and returns duration
int convertTimeAndDurationToTime(int, int);

#endif