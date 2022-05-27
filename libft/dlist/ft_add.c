/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:46:25 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/25 14:15:13 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_dlist	*ft_dlst_add(t_dlist *prev, void *content)
{
	t_dlist	*new;

	if (!content)
		return (prev);
	new = ft_calloc(1, sizeof(t_dlist));
	if (prev)
		prev->next = new;
	new->previous = prev;
	new->content = content;
	return (new);
}
