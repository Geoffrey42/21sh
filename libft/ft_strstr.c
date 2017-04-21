/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 08:47:44 by ggane             #+#    #+#             */
/*   Updated: 2016/11/16 08:48:20 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *s1, char *s2)
{
	size_t n;

	n = ft_strlen(s2);
	if (*s2 == '\0')
		return (s1);
	while (*s1)
		if (!ft_memcmp(s1++, s2, n))
			return (s1 - 1);
	return (0);
}
