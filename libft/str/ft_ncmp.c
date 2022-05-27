/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:16:37 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 09:22:49 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				ret;
	unsigned char	*s1cp;
	unsigned char	*s2cp;

	if (!n)
		return (0);
	i = 0;
	s1cp = (unsigned char *)s1;
	s2cp = (unsigned char *)s2;
	ret = s1cp[i] - s2cp[i];
	while ((!ret && i < n) && (s1[i] || s2[i]))
	{
		ret = s1cp[i] - s2cp[i];
		i++;
	}
	return (ret);
}
