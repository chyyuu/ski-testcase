#define _GNU_SOURCE
#include "ski-hyper.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	while((read = getline(&line, &len, stdin)) != -1){
		hypercall_debug_quiet(0, "%s", line);
	}
	free(line);
	return 0;
}
