#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

typedef struct s_data
{
	// once i = 32 add tmp to str and reset i
	char *str;
	int	data; //rename tmp
	int	i;
} t_data;

t_data data = {0, 0, 0x0};

void	signal_test(int signal)
{
	data.data <<= 1;
	if (signal == SIGUSR1)
	{
		ft_printf("1");
		data.data |= 1;
	}
	if (signal == SIGUSR2)
	{
		ft_printf("0");
		data.data |= 0;
	}
	data.i++;
	if (data.i == 33)
	{
		data.str[ft_strlen(data.str)] = data.data;
		ft_printf("\n==============================\n");
		ft_printf("end of transmission\n%d (%s) %s\n", data.data, ft_itoa_base(data.data, "01"), data.str);
		data.data = 0;
		data.i = 0;
	}
}

void	set_singnal_action(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));

	act.sa_handler = &signal_test;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int	main(void)
{
	data.str = malloc(500);
	if (data.str == NULL)
		exit(0);
	set_singnal_action();
	printf("PID: %d\n", getpid());
	while (1)
	{
		continue;
	}
	return 0;
}