#define _POSIX_C_SOURCE 200112L
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int	pid = 0;

void	send_letter(int c, char *bin)
{
	int	i;
	int	len;

	len = ft_strlen(bin);
	i = sizeof(int) * 8;
	ft_printf("sending %c (%s) to server\n", c, bin);
	while (i >= 0)
	{
		if (i < len)
		{
			if (bin[len - i - 1] == '1')
			{
				// ft_printf("sending SIGURS1 (1)\n");
				kill(pid, SIGUSR1); // |= 1
			}
			else
			{
				// ft_printf("sending SIGURS2 (0)\n");
				kill(pid, SIGUSR2); // |= 0
			}
		}
		else
		{
			// ft_printf("sending SIGURS2 (0)\n");
			kill(pid, SIGUSR2); // |= 0
		}

		usleep(1);
		i--;
	}
}

void	send_str(const char *str)
{
	int	i = 0;
	while (str[i])
	{
		send_letter(str[i], ft_itoa_base(str[i], "01"));
		i++;
	}
	send_letter('\0', ft_itoa_base('\0', "01"));

}

int main(int argc, char **argv)
{
	if (argc == 1)
		return (0);

	pid = atoi(argv[1]);
	ft_printf("setting server pid to %d\n", pid);

	send_str("hello world!\n");
}

