/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:48:38 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 09:22:48 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_utoa(unsigned int n)
{
	char			*ret;
	unsigned int	i;

	if (n == 4294967295)
		return (ft_strdup("4294967295"));
	if (n == 0)
		return (ft_strdup("0"));
	i = 0;
	ret = ft_calloc(ft_ulen(n) + 1, sizeof(char));
	while (n)
	{
		ret[i++] = (n % 10) + '0';
		n = n / 10;
	}
	ft_strrev(&ret, 0);
	return (ret);
}
