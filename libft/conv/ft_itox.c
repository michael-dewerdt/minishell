/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:51:26 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 09:22:48 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_itox(unsigned long int n, const char *base)
{
	char			*ret;
	size_t			i;
	unsigned int	neg;
	size_t			size;

	size = ft_longbaselen(n, 16);
	if (n == 0)
		return (ft_strdup("0"));
	i = 0;
	neg = 0;
	ret = ft_calloc(size + 1, sizeof(char));
	while (n)
	{
		ret[i++] = base[n % 16];
		n = n / 16;
	}
	ft_strrev(&ret, neg);
	return (ret);
}
