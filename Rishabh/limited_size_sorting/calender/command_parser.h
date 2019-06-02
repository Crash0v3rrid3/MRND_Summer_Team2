#ifndef _command_parser_h
#define _command_parser_h
#define WORKING_DAYS_COMMAND "workingDays"
#define STARTING_DAY_COMMAND "startingDay"
#define WORKING_HOURS_COMMAND

enum op { INVALID_INPUT = -1, INIT, ADD_PERSON, ADD_EVENT, SET_WORKING_DAYS, SET_STARTING_DAY, SET_WORKING_HOURS, LIST_EVENTS, IS_EVENT_POSSIBLE, NEXT_3_POSSIBLE_SLOTS, EXIT };

// takes in command input, parses it and stores args in the 2d array, return type of command
int parseInput(char *, void ***, int *);

#endif