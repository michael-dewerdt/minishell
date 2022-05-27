/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:43:48 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/25 14:56:37 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_split(const char *str, char c)
{
	t_dlist		*words;
	char		*word;
	int			i;
	int			j;

	i = -1;
	word = NULL;
	words = NULL;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if (!word && str[i] != c)
			j = 0;
		if (!word && str[i] != c)
			word = ft_calloc((int)ft_strlen_to(str + i, c) + 1, sizeof(char));
		if (word && str[i] == c)
			words = ft_dlst_add(words, word);
		if (word && str[i] == c)
			word = NULL;
		if (str[i] != c)
			word[j++] = str[i];
	}
	words = ft_dlst_add(words, word);
	return (ft_dlst_to_arr(words));
}
