/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:22:49 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/25 14:19:02 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_ilst_is_in(int value, t_i_slist lst)
{
	if (lst.nb == value && lst.next)
		return (1);
	while (lst.next)
	{
		if (lst.nb == value)
			return (1);
		else
			lst = *(lst.next);
	}
	return (0);
}
