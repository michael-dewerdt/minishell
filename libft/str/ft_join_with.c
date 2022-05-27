/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_with.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narnaud <narnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:44:59 by narnaud           #+#    #+#             */
/*   Updated: 2022/05/17 09:56:37 by narnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_with(char *s1, char *s2, char *inter)
{	
	int		path_length;
	char	*ret;

	path_length = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(inter) + 1;
	ret = ft_calloc(path_length, sizeof(char));
	ft_memcpy(ret, s1, ft_strlen(s1));
	ft_memcpy(ret + ft_strlen(s1), inter, ft_strlen(inter));
	ft_memcpy(ret + ft_strlen(s1) + ft_strlen(inter), \
		s2, ft_strlen(s2));
	return (ret);
}
