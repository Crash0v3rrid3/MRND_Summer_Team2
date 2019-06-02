#include "command_parser.h"

int parseInput(char *input, void ***args, int *numberOfArgs) {
	char command[30] = { 0 };
	int itr1, itr2;

	for (itr1 = 0; input[itr1] != ' '; ++itr1) {
		command[itr1] = input[itr1];
	}


}