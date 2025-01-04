/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:38:16 by mjuncker          #+#    #+#             */
/*   Updated: 2025/01/04 13:56:22 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	send_bit(char bit, int serv_pid)
{
	if (bit == '1')
		kill(serv_pid, SIGUSR1);
	else
		kill(serv_pid, SIGUSR2);
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
	if (bin == NULL)
		return ;
	send_data(bin, serv_pid);
	free(bin);
	bin = ft_itoa_base(header->msg_size, "01");
	if (bin == NULL)
		return ;
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
		if (bin == NULL)
			return ;
		send_data(bin, serv_pid);
		free(bin);
		i++;
	}
	bin = u_ft_itoa_base('\0', "01");
	if (bin == NULL)
		return ;
	send_data(bin, serv_pid);
	free(bin);
}

int	main(int argc, char **argv)
{
	int	serv_pid;

	signal(SIGUSR1, &handle_sig);
	signal(SIGUSR2, &handle_sig);
	if (argc != 3 || check_arg(argv[1]) == 1)
	{
		ft_printf("invalid params\n");
		return (0);
	}
	serv_pid = ft_atoi(argv[1]);
	if (serv_pid == 0)
	{
		ft_printf("invalid params\n");
		return (0);
	}
	ft_printf("sending message to server (%d)\n", serv_pid);
	send_str(argv[2], serv_pid);
}
