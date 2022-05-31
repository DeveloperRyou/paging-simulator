#include "paging.hh"

int parse_option(char *str)
{
	// check valid option
	for (int i=0;i<6;i++)
		if (str[i] != "-page="[i])
			return 0;
	str += 6;
	// parse option
	if (strcmp(str, "fifo"))
		return 1;
	else if (strcmp(str, "stack"))
		return 2;
	else if (strcmp(str, "sampled"))
		return 3;
	else if (strcmp(str, "second-chance"))
		return 4;
	else if (strcmp(str, "lfu"))
		return 5;
	else if (strcmp(str, "mfu"))
		return 6;
	else if (strcmp(str, "optimal"))
		return 7;
	return 0;
}
