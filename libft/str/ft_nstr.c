/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:52:56 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 09:22:49 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	int		found;

	i = 0;
	j = 0;
	found = 0;
	while (haystack[i] && i < len && needle[j])
	{
		if (haystack[i] == needle[j])
		{
			found = 1;
			j++;
		}
		else if (found)
		{
			found = 0;
			i -= j;
			j = 0;
		}
		i++;
	}
	if (!needle[j])
		return ((char *)(haystack + i - j));
	return (0);
}
