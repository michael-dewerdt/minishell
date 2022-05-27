/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:49:37 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 09:22:49 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_search_char(char c, char const *set)
{
	size_t	i;
	size_t	set_len;

	if (!c)
		return (0);
	i = 0;
	set_len = ft_strlen(set);
	while (i < set_len)
		if (c == set[i++])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	b_out;
	unsigned int	e_out;
	char			*ret;

	if (!s1)
		return (NULL);
	i = 0;
	b_out = 0;
	e_out = ft_strlen(s1);
	while (ft_search_char(s1[b_out], set))
		b_out++;
	while (e_out > b_out && ft_search_char(s1[e_out - 1], set))
		e_out--;
	ret = malloc((e_out - b_out + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (b_out < e_out)
		ret[i++] = s1[b_out++];
	ret[i] = '\0';
	return (ret);
}
