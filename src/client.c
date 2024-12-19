/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:38:16 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/19 11:19:10 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int	g_header_send = 0;

void	send_bit(char bit, int serv_pid)
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
		if (i < len)
			send_bit(bin[len - i - 1], serv_pid);
		else
			send_bit(0, serv_pid);
		i--;
	}
}

void	send_header(const t_header *header, int serv_pid)
{
	char	*bin;

	bin = ft_itoa_base(header->pid, "01");
	send_data(bin, serv_pid);
	free(bin);
	bin = ft_itoa_base(header->msg_size, "01");
	send_data(bin, serv_pid);
	free(bin);
}

void	send_str(const char *str, int serv_pid)
{
	t_header	header;
	int			i;
	char		*bin;

	header.pid = getpid();
	header.msg_size = (ft_strlen(str) + 1) * sizeof(char);
	send_header(&header, serv_pid);
	i = 0;
	while (str[i])
	{
		bin = u_ft_itoa_base(str[i], "01");
		send_data(bin, serv_pid);
		free(bin);
		i++;
	}
	bin = u_ft_itoa_base('\0', "01");
	send_data(bin, serv_pid);
	free(bin);
	ft_printf("message sent!\n");
}

int	main(int argc, char **argv)
{
	int	serv_pid;

	signal(SIGUSR1, &handle_sig);
	if (argc != 3 || check_arg(argv[1]) == 1)
	{
		ft_printf("invalide params\n");
		return (0);
	}
	serv_pid = atoi(argv[1]);
	if (serv_pid == 0)
	{
		ft_printf("invalide params\n");
		return (0);
	}
	ft_printf("sending message to server (%d)\n", serv_pid);
	if (argc == 3)
		send_str(argv[2], serv_pid);
}
