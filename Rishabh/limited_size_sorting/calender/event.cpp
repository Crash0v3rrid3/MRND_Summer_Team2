#include "event.h"
#include <stdlib.h>
#include <string.h>

Event *newEvent(char *name, unsigned int startTime, unsigned int endTime, unsigned int day) {
	Event *event = (Event *)calloc(sizeof(Event), 1);
	strncpy(event->name, name, 30);
	event->day = day;
	event->startTime = startTime;
	event->endTime = endTime;

	return event;
}