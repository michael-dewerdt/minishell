/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:12:01 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 09:22:49 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	get_nbrlength(int nbr)
{
	size_t	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr && ++i)
		nbr = nbr / 10;
	return (i);
}

static int	pow_10(size_t n)
{
	int	ret;

	if (!n)
		return (1);
	ret = 10;
	while (--n)
		ret *= 10;
	return (ret);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		fact;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	fact = pow_10(get_nbrlength(n) - 1);
	while (fact >= 10)
	{
		ft_putchar_fd(n / fact + '0', fd);
		n = n % fact;
		fact /= 10;
	}
	ft_putchar_fd(n + '0', fd);
}
