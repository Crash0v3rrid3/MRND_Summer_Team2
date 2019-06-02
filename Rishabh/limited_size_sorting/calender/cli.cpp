#include "cli.h"
#include "command_parser.h"
#include "person.h"
#include "event.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int startCli() {
	Person *persons = 0, **personsPass;
	int numberOfPersons = 0, typeOfCommand, numberOfArguments;
	int startDay, workingHoursStartTime, workingHoursEndTime, itr1, itr2, workingDays[7] = { 0 };
	char command[256];
	void **args;
	Event *event = 0, **events = NULL;

	while (1) {
		printf(COMMAND_PROMPT);
		fgets(command, 256, stdin);

		typeOfCommand = parseInput(command, &args, &numberOfArguments);
		
		switch (typeOfCommand) {
		case INVALID_INPUT: printf("Incorrect Command!\n");
		case INIT: persons = 0; 
			numberOfPersons = 0; 
			startDay = workingHoursEndTime = workingHoursStartTime = -1; 
			break;
		case SET_STARTING_DAY: startDay = *((int **)args)[0]; break;
		case SET_WORKING_DAYS: 
			for (itr1 = 0; itr1 < numberOfArguments; ++itr1) {
				for (itr2 = 0; itr2 < NUMBER_OF_DAYS; ++itr2) {
					if (!strcmp(((char **)args)[itr1], daysOfAWeek[itr2])) {
						workingDays[itr2] = 1;
						break;
					}
				}
			}
			break;
		case SET_WORKING_HOURS: workingHoursStartTime = *(int *)args[0];
			workingHoursEndTime = *(int *)args[1];
			break;
		case ADD_PERSON: 
			for (itr1 = 0; itr1 < numberOfArguments; ++itr1) {
				createPerson(&persons, numberOfPersons, ((char **)args)[itr1]);
				numberOfPersons++;
			}
			break;
		case ADD_EVENT: 
			event = newEvent(((char **)args)[0], *((int **)args)[1], *(int *)args[2], *(int *)args[3]);

			for (itr1 = 4; itr1 < numberOfArguments; itr1++) {
				itr2 = findPersonId(persons, numberOfPersons, ((char **)args)[itr1]);
				if (itr2 >= 0) {
					addNewEvent(persons + itr2, event, *(int *)args[1]);
				}
			}
			break;
		case LIST_EVENTS: 
			if (numberOfArguments > 0) {
				itr2 = findPersonId(persons, numberOfArguments, ((char **)args)[1]);
				if (itr2 >= 0)
					listEvents(persons + itr2);
			}	else	{
				listAllEvents(events);
			}
			break;
		case IS_EVENT_POSSIBLE: 
			event = newEvent("Untitled", *((int **)args)[numberOfArguments - 2], *(int *)args[numberOfArguments - 1], *(int *)args[3]);
			if (checkAvailability(persons, (char **)args, numberOfArguments - 3, event)) {
				printf("All users are jobless, you want to host the event (Y/N)?\n->");
				scanf("%c", &itr2);

				if (itr2 == 'Y' || itr2 == 'y') {
					printf("Enter name: ");
					fgets(command, 30, stdin);
					strncpy(event->name, command, 30);

					for (itr1 = 0; itr1 < numberOfArguments - 3; itr1++) {
						itr2 = findPersonId(persons, numberOfPersons, ((char **)args)[itr1]);
						if (itr2 >= 0) {
							addNewEvent(persons + itr2, event, *((int **)args)[1]);
						}
					}
				}	else	{
					personsPass = (Person **)malloc(sizeof(Person *) * (numberOfArguments - 3));
					for (itr1 = 0; itr1 < numberOfArguments - 3; ++itr1) {
						itr2 = findPersonId(persons, numberOfPersons, ((char **)args)[itr1]);
						personsPass[itr1] = persons + itr2;
					}
					event = findNextPossibleSlot(personsPass, numberOfArguments - 3, event);

					printf("Next possible event day = %u, startTime - %u, endTime - %u, duration - %u\n", event->day, event->startTime, event->endTime, *((int **)args)[numberOfArguments - 3]);
				}
			}
			break;
		case NEXT_3_POSSIBLE_SLOTS: 
			personsPass = (Person **)malloc(sizeof(Person *) * (numberOfArguments - 3));
			for (itr1 = 0; itr1 < numberOfArguments - 2; ++itr1) {
				personsPass[findPersonId(persons, numberOfPersons, ((char **)args)[itr1])] = persons + itr1;
			}
			event = newEvent("Untitled", 0, convertTimeAndDurationToTime(0, *((unsigned int **)args)[numberOfArguments - 1]), *((unsigned int **)args)[numberOfArguments - 2]);

			for (itr2 = 0; itr2 < 3; ++itr2) {
				event = findNextPossibleSlot(personsPass, numberOfArguments - 3, event);

				printf("%u possible event day = %u, startTime - %u, endTime - %u, duration - %u\n", itr2, event->day, event->startTime, event->endTime, *((int **)args)[numberOfArguments - 3]);
			}
			
		}
	}
}