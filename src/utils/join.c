/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 01:04:01 by piranucc          #+#    #+#             */
/*   Updated: 2017/04/20 01:04:24 by piranucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_join_path(int i, char **path, char **s, char *tmp)
{
	while (path[i])
		free(path[i++]);
	free(path);
	return (ft_path_finded(s, tmp));
}

int		ft_join_error(int i, char **path, char **s, char *tmp)
{
	while (path[i])
		free(path[i++]);
	free(path);
	return (ft_path_inacess(tmp, s));
}