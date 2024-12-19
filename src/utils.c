/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:27:53 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/18 16:16:31 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#if DEBUG

void	print_str(t_header data)
{
	ft_printf("\n");
	ft_printf("end of transmission\n");
	ft_printf("client pid: %d\nmsg size: %d\n", \
	data.header.pid, data.header.msg_size);
	ft_printf("%s\n", data.str);
	ft_printf("==============================\n");
}
#else

void	print_str(t_data data)
{
	ft_printf("%s\n", data.str);
}
#endif

void	handle_sig(int signal)
{
	if (signal == SIGUSR1)
	{
		return ;
	}
}

void	set_signal_action(void (*f)(int))
{
	struct sigaction	act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = f;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int	check_bit(int signal)
{
	if (signal == SIGUSR1)
		return (1);
	if (signal == SIGUSR2)
		return (0);
	return (-1);
}
