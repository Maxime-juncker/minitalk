/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:38:16 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/18 16:17:06 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int	g_header_send = 0;

void	send_bit(char bit, int i, int len, int serv_pid)
{
	if (i < len)
	{
		if (bit == '1')
		{
			kill(serv_pid, SIGUSR1);
			if (g_header_send)
				pause();
		}
		else
		{
			kill(serv_pid, SIGUSR2);
			if (g_header_send)
				pause();
		}
	}
	else
	{
		kill(serv_pid, SIGUSR2);
		if (g_header_send)
			pause();
	}
	usleep(WAITIME);
}

void	send_data(char *bin, int serv_pid)
{
	int	i;
	int	len;

	len = ft_strlen(bin);
	i = sizeof(int) * 8;
	while (i >= 0)
	{
		send_bit(bin[len - i - 1], i, len, serv_pid);
		i--;
	}
}

void	send_header(const t_header *header, int serv_pid)
{
	char	*bin;

	ft_printf("pid: %d\n", header->pid);
	ft_printf("msg size: %d\n", header->msg_size);
	bin = ft_itoa_base(header->pid, "01");
	ft_printf("sending pid (%s)\n", bin);
	send_data(bin, serv_pid);
	bin = ft_itoa_base(header->msg_size, "01");
	ft_printf("sending msg size (%s)\n", bin);
	send_data(bin, serv_pid);
}

void	send_str(const char *str, int serv_pid)
{
	t_header	header;
	int			i;

	header.pid = getpid();
	header.msg_size = (ft_strlen(str) + 1) * sizeof(char);
	send_header(&header, serv_pid);
	i = 0;
	while (str[i])
	{
		send_data(u_ft_itoa_base(str[i], "01"), serv_pid);
		i++;
	}
	send_data(u_ft_itoa_base('\0', "01"), serv_pid);
}

int	main(int argc, char **argv)
{
	int	serv_pid;

	signal(SIGUSR1, &handle_sig);
	if (argc <= 1)
		return (0);
	serv_pid = atoi(argv[1]);
	ft_printf("setting server pid to %d\n", serv_pid);
	if (argc == 3)
		send_str(argv[2], serv_pid);
}
