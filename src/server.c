#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

void	signal_test(int signal)
{
	if (signal == SIGUSR1)
		write(1, "\nInterecpted SIGUSR1!\n", strlen("\nInterecpted SIGUSR1!\n"));
	if (signal == SIGUSR2)
		write(1, "\nInterecpted SIGUSR2!\n", strlen("\nInterecpted SIGUSR2!\n"));
}

void	set_singnal_action(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));

	act.sa_handler = &signal_test;
	sigaction(SIGUSR1, &act, NULL);
}

int	main(void)
{
	set_singnal_action();
	printf("PID: %d\n", getpid());
	while (1)
	{
		continue;
	}
	return 0;
}