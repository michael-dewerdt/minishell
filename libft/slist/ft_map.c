/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:54:31 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 11:31:05 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_slist	*ft_slst_map(t_slist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_slist	*new_lst;

	if (!lst || !f)
		return (NULL);
	new_lst = ft_slst_new((*f)(lst->content));
	if (!new_lst)
	{
		ft_slst_clear(&new_lst, del);
		return (NULL);
	}
	new_lst->next = ft_slst_map(lst->next, f, del);
	return (new_lst);
}
