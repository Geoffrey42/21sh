/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:56:01 by piranucc          #+#    #+#             */
/*   Updated: 2017/04/20 00:08:01 by piranucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

int		free_and_quit(char *str)
{
	free(str);
	return (0);
}

char	**free_and_quit_null(char *str)
{
	free(str);
	return (NULL);
}