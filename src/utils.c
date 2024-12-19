/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:27:53 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/19 14:58:45 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_sig(int signal)
{
	if (signal == SIGUSR1)
		return ;
	if (signal == SIGUSR2)
	{
		ft_printf("server has receive message!\n");
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

int	check_arg(char *argv1)
{
	int	i;

	if (argv1 == NULL)
		return (1);
	i = 0;
	while (argv1[i])
	{
		if (!ft_isdigit(argv1[i]))
			return (1);
		i++;
	}
	return (0);
}
