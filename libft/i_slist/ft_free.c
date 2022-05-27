/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 09:27:41 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/25 14:18:37 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_ilst_free(t_i_slist *list)
{
	t_i_slist	*next;

	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}
