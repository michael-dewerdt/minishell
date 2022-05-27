/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:06:25 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/25 14:14:45 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	double	nb;

	nb = 0;
	sign = 1;
	if (!ft_strncmp(str, "-2147483648", 11))
		return (-2147483648);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' && ++str)
		sign = -1;
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0') % 10;
		if (nb > 2147483647 && sign > 0)
			return (-1);
		else if (nb > 2147486648 && sign < 0)
			return (0);
		str++;
	}
	return ((int)(sign * nb));
}
