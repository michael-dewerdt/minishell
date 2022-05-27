/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:53:04 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 11:31:05 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_slst_clear(t_slist **lst, void (*del)(void *))
{
	t_slist	*next_cell;

	if (!del)
		return ;
	while (lst && *lst)
	{
		next_cell = (*lst)->next;
		ft_slst_delone(*lst, del);
		*lst = next_cell;
	}
}
