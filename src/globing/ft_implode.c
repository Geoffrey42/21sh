/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_implode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:56:01 by piranucc          #+#    #+#             */
/*   Updated: 2017/04/20 00:06:25 by piranucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int	find_size(char **split, char *inter)
{
	int	i;
	int	size;
	int	len_inter;

	i = 0;
	size = 0;
	len_inter = ft_strlen(inter);
	while (split[i])
	{
		size += ft_strlen(split[i]);
		i++;
		if (split[i])
			size += len_inter;
	}
	size += 1;
	return (size);
}

char		*ft_implode(char **split, char *inter)
{
	char	*result;
	int		size;
	int		i;

	size = find_size(split, inter);
	result = ft_strnew(size);
	i = 0;
	while (split[i])
	{
		ft_strcat(result, split[i]);
		i++;
		if (split[i])
			ft_strcat(result, inter);
	}
	return (result);
}