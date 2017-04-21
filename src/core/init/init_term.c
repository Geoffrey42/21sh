/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:06:04 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:12:12 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	init_std(t_var *var)
{
	tcgetattr(0, &var->termios);
	var->termios.c_lflag |= (ICANON | ECHO | ISIG | ECHOCTL);
	tcsetattr(0, 0, &var->termios);
}

void	init_termios(t_var *var)
{
	char	*name;

	if ((name = getenv("TERM")) == NULL)
		name = ft_strdup("xterm-256color");
	if (tgetent(NULL, name) <= 0)
		return ;
	if (tcgetattr(0, &var->termios) == -1)
	{
		miniprintf(STDERR_FILENO, "21sh error: no termios.");
		exit(F);
	}
	var->termios.c_lflag &= ~(ICANON | ECHO | ISIG | ECHOCTL);
	var->termios.c_cc[VMIN] = 1;
	var->termios.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &var->termios) == -1)
		return ;
}
