#include <minitalk.h>
#include <fcntl.h>

void	handle_sig(int signal)
{
	if (signal == SIGUSR1)
	{
		return ;
	}

}
int header_sent = 0;

void	send_data(char *bin, int msg_size, int serv_pid)
{
	int	i;
	int	len;

	len = ft_strlen(bin);
	i = msg_size;

	while (i >= 0)
	{
		if (i < len)
		{
			if (bin[len - i - 1] == '1')
			{
				// ft_printf("sending SIGURS1 (1)\n");
				kill(serv_pid, SIGUSR1); // |= 1
			}
			else
			{
				// ft_printf("sending SIGURS2 (0)\n");
				kill(serv_pid, SIGUSR2); // |= 0
			}
		}
		else
		{
			// ft_printf("sending SIGURS2 (0)\n");
			kill(serv_pid, SIGUSR2); // |= 0

		}
		if (header_sent == 1)
			pause();
		else
			usleep(15);
		i--;
	}
}

void	send_letter(char *bin, int serv_pid)
{
	send_data(bin, sizeof(char) * 8, serv_pid);
}

void	send_header(const t_header *header, int serv_pid)
{
	char	*bin;
	ft_printf("pid: %d\n", header->pid);
	ft_printf("msg size: %d\n", header->msg_size);

	bin = ft_itoa_base(header->pid, "01");
	ft_printf("sending pid (%s)\n", bin);
	send_data(bin, sizeof(int) * 8, serv_pid);
	bin = ft_itoa_base(header->msg_size, "01");
	ft_printf("sending msg size (%s)\n", bin);
	send_data(bin, sizeof(int) * 8, serv_pid);

}

void	send_str(const char *str, int serv_pid)
{
	t_header	header;

	header.pid = getpid();
	header.msg_size = ft_strlen(str) * sizeof(char);

	send_header(&header, serv_pid);

	int	i = 0;
	while (str[i])
	{
		send_letter(ft_itoa_base(str[i], "01"), serv_pid);
		i++;
	}
	send_letter(ft_itoa_base('\0', "01"), serv_pid);

}

int main(int argc, char **argv)
{
	int	serv_pid;
	// char	*txt;

	signal(SIGUSR1, handle_sig);

	if (argc <= 1)
		return (0);

	serv_pid = atoi(argv[1]);
	ft_printf("setting server pid to %d\n", serv_pid);

	if (argc == 3)
	{
		send_str(argv[2], serv_pid);
		return 0;
	}

	send_str("Hello, World!", serv_pid);
	// send_str("emoji : ✊");
	// send_str("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean m");
}

