#include <minitalk.h>

typedef struct s_data
{
	t_header	header;

	int	header_received;
	int	tmp;
	size_t	bit_received;
} t_data;

t_data data = {{0, 0}, 0, 0, 0};

void	receive_header(int signal)
{
	if (data.bit_received <= sizeof(int) * 8)
	{
		data.header.pid <<= 1;
		if (signal == SIGUSR1)
		{
			// ft_printf("1", data.bit_received);
			data.header.pid |= 1;
		}
		if (signal == SIGUSR2)
		{
			// ft_printf("0", data.bit_received);
			data.header.pid |= 0;
		}
		data.bit_received++;
		return ;
	}
	else if (data.bit_received - 1 <= sizeof(int) * 8 * 2)
	{
		data.header.msg_size <<= 1;
		if (signal == SIGUSR1)
		{
			data.header.msg_size |= 1;
		}
		if (signal == SIGUSR2)
		{
			data.header.msg_size |= 0;
		}
		data.bit_received++;
		if (data.bit_received - 1 <= sizeof(int) * 8 * 2)
			return ;
	}
	data.bit_received = 0;
	data.header_received = 1;
}

void	signal_test(int signal)
{

	if (data.header_received == 0)
	{
		receive_header(signal);
		return ;
	}
	data.tmp <<= 1;
	if (signal == SIGUSR1)
	{
		data.tmp |= 1;
	}
	if (signal == SIGUSR2)
	{
		data.tmp |= 0;
	}
	data.bit_received++;
	if (data.bit_received == 9)
	{
		if (data.tmp == 0)
		{
			ft_printf("==============================\n");
			ft_printf("end of transmission\n");
			ft_printf("client pid: %d\nmsg size: %d\n", data.header.pid, data.header.msg_size);
			data.tmp = 0;
			data.bit_received = 0;
			data.header_received = 0;
			data.header.pid = 0;
			data.header.msg_size = 0;
			return ;
		}
		ft_printf("%c", data.tmp);
		data.tmp = 0;
		data.bit_received = 0;
	}
	kill(data.header.pid, SIGUSR1);
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
	set_singnal_action();
	printf("PID: %d\n", getpid());
	while (1)
	{
		continue;
	}
	return 0;
}