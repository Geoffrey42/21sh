/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pv_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:55:03 by piranucc          #+#    #+#             */
/*   Updated: 2017/04/13 15:56:32 by piranucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_init_supp(char **ret, char *s, int *i, int *j)
{
	*ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	ft_bzero(*ret, ft_strlen(s));
	*i = 0;
	*j = 0;
	while (s[*i] == ' ')
		(*i)++;
}
