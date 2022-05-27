/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:36:09 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 11:31:05 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_slist	*ft_slst_new(void *content)
{
	t_slist	*i_cell;

	i_cell = (t_slist *)malloc(sizeof(*i_cell));
	if (!i_cell)
		return (NULL);
	i_cell->content = content;
	i_cell->next = NULL;
	return (i_cell);
}
