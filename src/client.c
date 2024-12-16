#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int	pid = 0;

int main(int argc, char **argv)
{
	if (argc == 1)
		return (0);

	pid = atoi(argv[1]);
	ft_printf("setting server pid to %d\n", pid);
	char a = 'a';
	char *bin;
	ft_printf("preparing to send '%c' to server\n", a);
	bin = ft_itoa_base(a, "01");
	ft_printf("binary: %s\n\n", bin);

	// sending bin
	int	i = sizeof(int) * 8;
	int	len = ft_strlen(bin);
	ft_printf("len: %u\n", len);

	// debug print
	while (i >= 0)
	{
		if (i < len)
		{
			ft_printf("%c", bin[len - i - 1]);
		}
		else
		{
			ft_printf("0");
		}
		i--;
	}
	ft_printf("\n\n");

	int res = 0; // 0 (0000)
	i = sizeof(int) * 8;
	while (i >= 0)
	{
		res <<= 1;
		if (i < len)
		{
			if (bin[len - i - 1] == '1')
				res |= 1;
			else
				res |= 0;
			// ft_printf("%c", bin[len - i - 1]);
		}
		i--;
	}
	ft_printf("res: %d (%s)", res, ft_itoa_base(res, "01"));
}

