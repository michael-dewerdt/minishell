/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:42:43 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 09:22:49 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_ilen(int nbr)
{
	size_t	i;

	i = 0;
	if (nbr == 0)
		return (1);
	else if (nbr < 0)
		i++;
	while (nbr && ++i)
		nbr = nbr / 10;
	return (i);
}

size_t	ft_ulen(unsigned int nbr)
{
	size_t	i;

	i = 0;
	while (nbr && ++i)
		nbr = nbr / 10;
	return (i);
}

size_t	ft_longbaselen(long nbr, size_t base)
{
	size_t	i;

	if (nbr <= 0)
		i = 1;
	else
		i = 0;
	while (nbr && ++i)
		nbr = nbr / base;
	return (i);
}
