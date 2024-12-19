/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:36:07 by mjuncker          #+#    #+#             */
/*   Updated: 2024/12/19 11:44:39 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nb_len_base(int n, int base_len)
{
	size_t		i;
	long int	nb;

	i = 1;
	nb = (long)n;
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb / base_len > 0)
	{
		i++;
		nb /= base_len;
	}
	return (i);
}

char	*ft_itoa_base(int n, const char *base)
{
	long int	nb;
	char		*res;
	size_t		i;
	size_t		len;

	len = get_nb_len_base(n, ft_strlen(base));
	nb = (long)n;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	if (n == 0)
		res[0] = '0';
	if (nb < 0)
	{
		nb *= -1;
		res[0] = '-';
	}
	while (nb > 0)
	{
		res[len - i++ - 1] = base[(nb % ft_strlen(base))];
		nb /= ft_strlen(base);
	}
	res[len] = '\0';
	return (res);
}

static size_t	uget_nb_len(unsigned int n, int base_len)
{
	size_t		i;
	long int	nb;

	nb = (long)n;
	i = 1;
	while (nb / base_len > 0)
	{
		i++;
		nb /= base_len;
	}
	return (i);
}

char	*u_ft_itoa_base(unsigned int n, const char *base)
{
	unsigned long int	nb;
	char				*res;
	size_t				i;
	size_t				len;

	len = uget_nb_len(n, ft_strlen(base));
	nb = (unsigned long)n;
	res = malloc(len + 1);
	i = 0;
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	while (nb > 0)
	{
		res[len - i++ - 1] = base[nb % ft_strlen(base)];
		nb /= ft_strlen(base);
	}
	res[len] = '\0';
	return (res);
}
