#include "paging.hh"

int parse_option(char *str)
{
	// check valid option
	for (int i=0;i<6;i++)
		if (str[i] != "-page="[i])
			return 0;
	str += 6;
	// parse option
	if (strcmp(str, "fifo") == 0)
		return 1;
	else if (strcmp(str, "stack") == 0)
		return 2;
	else if (strcmp(str, "sampled") == 0)
		return 3;
	else if (strcmp(str, "second-chance") == 0)
		return 4;
	else if (strcmp(str, "lfu") == 0)
		return 5;
	else if (strcmp(str, "mfu") == 0)
		return 6;
	else if (strcmp(str, "optimal") == 0)
		return 7;
	return 0;
}
