/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_to_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:50:10 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 11:33:57 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_dlst_to_arr(t_dlist	*ptr)
{
	char	**ret;
	t_dlist	*last;
	t_dlist	*tmp;
	size_t	count;

	last = ptr;
	count = 1;
	if (!ptr)
		return (ft_calloc(1, sizeof(char *)));
	while (ptr->previous)
	{
		ptr = ptr->previous;
		count++;
	}
	ret = ft_calloc(count + 1, sizeof(char *));
	ret[count] = NULL;
	while (count--)
	{
		ret[count] = last->content;
		tmp = last->previous;
		free(last);
		last = tmp;
	}
	return (ret);
}
