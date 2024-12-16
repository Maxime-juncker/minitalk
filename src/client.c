#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int	pid = 0;

void	signal_test(int signal)
{
	write(1, "\nInterecpted SIGINT!\n", strlen("\nInterecpted SIGINT!\n"));
	if (signal == SIGINT)
		kill(pid, SIGUSR1);
	// if (signal == SIGUSR1)
	// 	write(1, "\nInterecpted SIGUSR1!\n", strlen("\nInterecpted SIGUSR1!\n"));
	// if (signal == SIGUSR2)
	// 	write(1, "\nInterecpted SIGUSR2!\n", strlen("\nInterecpted SIGUSR2!\n"));
}

void	set_singnal_action(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));

	act.sa_handler = &signal_test;
	sigaction(SIGINT, &act, NULL);
}

int main(int argc, char **argv)
{
	if (argc == 1)
		return (0);

	pid = atoi(argv[1]);
	printf("sending signal to %dpid\n", pid);
	set_singnal_action();
	while (1)
	{
		continue;
	}
}

