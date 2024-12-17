#include <minitalk.h>

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

	signal(SIGUSR1, handle_sig);
	signal(SIGUSR2, handle_sig);

	if (argc == 1)
		return (0);

	serv_pid = atoi(argv[1]);
	ft_printf("setting server pid to %d\n", serv_pid);

	// send_str("hello world!", serv_pid);

	// 100 char test
	// send_str("emoji : ✊");
	// send_str("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean m");
	send_str("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Etiam rhoncus. Maecenas tempus, tellus eget condimentum rhoncus, sem quam semper libero, sit amet adipiscing sem neque sed ipsum. Nam quam nunc, blandit vel, luctus pulvinar, hendrerit id, lorem. Maecenas nec odio et ante tincidunt tempus. Donec vitae sapien ut libero venenatis faucibus. Nullam quis ante. Etiam sit amet orci eget eros faucibus tincidunt. Duis leo. Sed fringilla mauris sit amet nibh. Donec sodales sagittis magna. Sed consequat, leo eget bibendum sodales, augue velit cursus nunck!", serv_pid);
}

