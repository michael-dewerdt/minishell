/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 09:06:44 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/25 13:26:04 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_ilst_first(t_i_slist *lst, int (*fct)(int a, int b))
{
	int		previous;
	size_t	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst)
	{
		previous = lst->nb;
		lst = lst->next;
		if (lst && fct(previous, lst->nb))
			return (i);
		i++;
	}
	return (-1);
}
