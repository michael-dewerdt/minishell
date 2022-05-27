/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:50:47 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 09:22:48 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_itoa(int n)
{
	char			*ret;
	unsigned int	i;
	unsigned int	neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	i = 0;
	neg = 0;
	ret = ft_calloc(ft_ilen(n) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	while (n)
	{
		ret[i++] = (n % 10) + '0';
		n = n / 10;
	}
	ft_strrev(&ret, neg);
	return (ret);
}
