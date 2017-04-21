/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piranucc <piranucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:56:01 by piranucc          #+#    #+#             */
/*   Updated: 2017/04/13 15:52:16 by piranucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_error(char *s)
{
	miniprintf(STDERR_FILENO, "%s : invalid. No arguments accepted.\n", s);
	return (0);
}

void	ft_error_malloc(void)
{
	miniprintf(STDERR_FILENO, "ERROR: out of memory! malloc() failed.\n");
	exit(1);
}