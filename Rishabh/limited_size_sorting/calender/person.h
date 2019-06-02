#include "date.h"
#ifndef _person_h
#define _person_h

typedef struct _Person {
	char name[30];
	Date calender[31];
} Person;

// Create a new person and store it persons array
void createPerson(Person **persons, int numberOfExistingPersons, char *newPersonName);

// Takes in person array, numberOfPersons, array of names, number of names and checks if all are available to attend that event
int checkAvailability(Person *, int, char **, int, Event *);

// Adds a new event to the persons calender
int addNewEvent(Person *person, Event *event);

// Searches for user in a user arr
int findPersonId(Person *, int numberOfPersons, char *);

// List all user events
void listEvents(Person *person);

// Find next possible slots on or after a particular day, takes 3 args, list of persons, numberOfPersons, day
Event *findNextPossibleSlot(Person **persons, int numberOfPersons, char **names, int numberOfNames, int duration);

// Finds n number of possible slots for k number
Event **findNNextPossibleSlots(Person **persons, int numberOfPersons, Event *, int numberOfSlots);

#endif