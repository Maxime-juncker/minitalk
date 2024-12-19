/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:34:17 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/19 15:00:13 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

t_data	g_data = {{0, 0}, 0, 0, 0, 0x0, 0};

void	receive_header(int signal)
{
	if (g_data.bit_received <= sizeof(int) * 8)
	{
		g_data.header.pid <<= 1;
		g_data.header.pid |= check_bit(signal);
		g_data.bit_received++;
		return ;
	}
	else if (g_data.bit_received - 1 <= sizeof(int) * 8 * 2)
	{
		g_data.header.msg_size <<= 1;
		g_data.header.msg_size |= check_bit(signal);
		g_data.bit_received++;
		if (g_data.bit_received - 1 <= sizeof(int) * 8 * 2)
			return ;
	}
	g_data.bit_received = 0;
	g_data.header_received = 1;
}

int	reset_data(void)
{
	if (g_data.tmp == 0)
	{
		ft_printf("%s\n", g_data.str);
		kill(g_data.header.pid, SIGUSR2);
		g_data.header.pid = 0;
		g_data.header.msg_size = 0;
		g_data.header_received = 0;
		g_data.tmp = 0;
		g_data.bit_received = 0;
		free(g_data.str);
		g_data.str = 0x0;
		g_data.str_len = 0;
		return (1);
	}
	else
	{
		g_data.str[g_data.str_len] = g_data.tmp;
		g_data.str_len++;
		g_data.tmp = 0;
		g_data.bit_received = 0;
	}
	return (0);
}

void	signal_receive(int signal)
{
	if (g_data.header_received == 0)
	{
		receive_header(signal);
		return ;
	}
	if (g_data.str == 0x0)
	{
		g_data.str = ft_calloc(g_data.header.msg_size + 1, 1);
		g_data.str_len = 0;
	}
	g_data.tmp <<= 1;
	g_data.tmp |= check_bit(signal);
	g_data.bit_received++;
	if (g_data.bit_received == 33)
	{
		if (reset_data() == 1)
		{
			return ;
		}
	}
	kill(g_data.header.pid, SIGUSR1);
}

int	main(void)
{
	ft_printf("PID: %d\n", getpid());
	set_signal_action(&signal_receive);
	while (1)
	{
		continue ;
	}
	return (0);
}
