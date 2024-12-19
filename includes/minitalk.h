/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:33:44 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/19 14:54:23 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 200112L
# define _DEFAULT_SOURCE

# ifndef WAITIME
#  define WAITIME 200
# endif

# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_header
{
	int	pid;
	int	msg_size;
}	t_header;

typedef struct s_data
{
	t_header	header;

	int			header_received;
	int			tmp;
	size_t		bit_received;
	char		*str;
	int			str_len;
}	t_data;

// utils.c
void	handle_sig(int signal);
void	set_signal_action(void (*f)(int));
int		check_bit(int signal);
int		check_arg(char *argv1);

#endif