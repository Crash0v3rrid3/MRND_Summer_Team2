#include "person.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createPerson(Person **persons, int numberOfExistingPersons, char *newPersonName) {
	if (numberOfExistingPersons > 0) {
		*persons = (Person *)realloc(*persons, sizeof(Person) * (numberOfExistingPersons + 1));
	}	else	{
		*persons = (Person *)calloc(sizeof(Person), 1);
	}

	strncpy(persons[numberOfExistingPersons]->name, newPersonName, 30);
	memset(persons[numberOfExistingPersons]->calender, 0, sizeof(persons[numberOfExistingPersons]->calender));
}

int numberFallsInRange(int rangeStart, int rangeEnd, int number) {
	return (rangeStart < number && number < rangeEnd);
}

int findPersonId(Person *persons, int numberOfPersons, char *name) {
	int itr;

	for (itr = 0; itr < numberOfPersons; ++itr) {
		if (!strcmp(persons[itr].name, name)) // if case insensitive implement strcmp
			return itr;
	}

	return -1;
}

int findPersonId(Person *persons, int numberOfPersons, char *name) {
	int itr;

	for (itr = 0; itr < numberOfPersons; ++itr) {
		if (!strcmp(name, persons[itr].name)) {
			return itr;
		}
	}

	return -1;
}

int checkAvailability(Person *persons, int numberOfPersons, char **names, int numberOfNames, Event *event) {
	int itr1, personId, itr2;

	for (itr1 = 0; itr1 < numberOfNames; ++itr1) {
		personId = findPersonId(persons, numberOfPersons, names[itr1]); // Person ID
		
		for (itr2 = 0; itr2 < persons[personId].calender[event->day].numberOfEvents; ++itr2) {
			if ((event->startTime >= persons[personId].calender[event->day].events[itr2]->startTime
				&& event->startTime <= persons[personId].calender[event->day].events[itr2]->endTime)
				|| (event->endTime >= persons[personId].calender[event->day].events[itr2]->startTime
				&& event->endTime <= persons[personId].calender[event->day].events[itr2]->endTime)) {
				return personId; // Can be 0->numberOfPersons
			}
		}
	}

	return -1; // Success!
}

int addNewEvent(Person *person, Event *event) {
	if (checkAvailability(person, 1, (char **)&(person->name), 1, event) != -1) {
		return 0;
	}
	int itr1, itr2;

	for (itr1 = 0; itr1 < person->calender[event->day].numberOfEvents; ++itr1) {
		if (event->startTime < person->calender[event->day].events[itr1]->startTime) {
			break;
		}
	}

	if (person->calender[event->day].numberOfEvents == 0) {
		person->calender[event->day].events = (Event **)calloc(1, sizeof(Event *));
	}	else {
		person->calender[event->day].events = (Event **)realloc(person->calender[event->day].events, (person->calender[event->day].numberOfEvents + 1) * sizeof(Event *));
		person->calender[event->day].numberOfEvents += 1;
		for (itr2 = person->calender[event->day].numberOfEvents - 1; itr2 > itr2; itr2--) {
			person->calender[event->day].events[itr2 + 1] = person->calender[event->day].events[itr2];
		}
		person->calender[event->day].events[itr1] = event;
	}

	return 1;
}

void printEvent(Event *event) {
	printf("[\"%s\", %u, %u, %u]\n", event->name, event->startTime, event->endTime, event->day);
}

void listEvents(Person *person) {
	int dateItr, eventItr;
	for (dateItr = 0; dateItr < 31; ++dateItr) {
		for (eventItr = 0; eventItr < person->calender[dateItr].numberOfEvents; ++eventItr) {
			printEvent(person->calender[dateItr].events[eventItr]);
		}
	}
}

Event *findNextPossibleSlot(Person **persons, int numberOfPersons, char **names, int numberOfNames, int duration) {
	Event event = { "", 0000, convertTimeAndDurationToTime(0, duration)};
}
