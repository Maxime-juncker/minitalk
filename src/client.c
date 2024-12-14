#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 1)
		return (0);

	int pid = atoi(argv[1]);
	kill(pid, SIGUSR1);
}

