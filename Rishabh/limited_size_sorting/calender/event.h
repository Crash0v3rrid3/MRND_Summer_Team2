#ifndef _event_h
#define _event_h

typedef struct _Event {
	char name[30];
	unsigned int startTime, endTime;
	unsigned int day;
} Event;

Event *newEvent(char *, unsigned int, unsigned int, unsigned int);
void listAllEvents(Event **);

#endif