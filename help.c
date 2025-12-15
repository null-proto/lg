#include "help.h"
#include <stdio.h>

void help_msg() {
	printf("Usage: dm [options]...\n\n");
	printf("    -a, --allow-term   -   removes tty only mode\n");
	printf("    -h, --help   -   prints help message\n");
}


void help_name_wargs(char* warg) {
	printf("dm: invalid option -- %s\n\n", warg);
}

void help_name_wflag(char warg) {
	printf("dm: invalid option -- %c\n\n", warg);
}
