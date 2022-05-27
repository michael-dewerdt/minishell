/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:51:11 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 11:31:05 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_slst_add_back(t_slist **alst, t_slist *new)
{
	t_slist	*i_cell;

	if (!alst || !new)
		return ;
	if (*alst)
	{
		i_cell = ft_slst_last(*alst);
		i_cell->next = new;
	}
	else
		*alst = new;
}
