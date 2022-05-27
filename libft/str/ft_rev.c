/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 09:36:21 by narnaud           #+#    #+#             */
/*   Updated: 2022/03/24 09:22:49 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_strrev(char **str, unsigned int neg)
{
	char	ch;
	size_t	size;
	size_t	i;

	size = ft_strlen(*str);
	if (neg)
		(*str)[size++] = '-';
	i = 0;
	while (i < size / 2)
	{
		ch = (*str)[i];
		(*str)[i] = (*str)[size - i - 1];
		(*str)[size - i - 1] = ch;
		i++;
	}
}
