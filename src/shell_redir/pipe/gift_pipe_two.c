/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gift_pipe_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 06:29:10 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 18:04:08 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		ft_free_loop_cmd(char ***cmd, int *i)
{
	while ((*cmd)[*i])
	{
		free((*cmd)[*i]);
		(*cmd)[*i] = NULL;
		(*i)++;
	}
}

void		ft_loop_red(t_var *var, int j, char ***cmd)
{
	int	i;
	int	fd;

	ft_init_loop_red(var);
	if (search_redir(var, j))
		if (var->red)
		{
			if (*(cmd + 1) != NULL)
				var->ifpipe = 1;
			redir_pipe(var, j);
			i = 0;
			var->ifpipe = 0;
			while (ft_search_redir((*cmd)[i]) == 0)
				i++;
			if (ft_search_redir((*cmd)[i]) == 1)
				ft_free_next_cmd(cmd, i);
			else if (ft_search_redir((*cmd)[i]) == 2)
				ft_loop_redir_spe(var, cmd, &i);
			else if (ft_search_redir((*cmd)[i]) == 3)
				ft_free_loop_cmd(cmd, &i);
		}
	var->oui = 0;
	(var->to == -1 && var->from == 2) ? ft_aggreg_close(var, &fd) : (0);
	(var->to == -1 && var->from == 1) ? *(cmd + 1) = NULL : (0);
}

void		ft_pid_repeat(t_var *var, int file, int p[2])
{
	char	buf[2];
	char	*tmp;
	int		fd_bis;

	tmp = ft_strdup("\0");
	fd_bis = open(var->redir[3], O_RDONLY);
	while (read(fd_bis, buf, 1))
	{
		tmp = ft_strjoin(tmp, buf);
		ft_bzero(buf, 2);
	}
	write(p[1], tmp, ft_strlen(tmp));
	write(file, tmp, ft_strlen(tmp));
	close(fd_bis);
	close(file);
	free(tmp);
	var->hdc = 0;
}

void		ft_pid_rep(t_var *var, int p[2])
{
	int	file;

	write(p[1], var->hdc_result, ft_strlen(var->hdc_result));
	if (!ft_strcmp(var->redir[4], ">"))
		file = open(var->redir[5], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file = open(var->redir[5], O_WRONLY | O_CREAT | O_APPEND, 0644);
	write(file, var->hdc_result, ft_strlen(var->hdc_result));
	ft_pid_repeat(var, file, p);
}

void		ft_heredoc_pipe(t_var *var, int p[2])
{
	char	buf[2];
	char	*tmp;
	char	*tmp1;
	int		fd_bis;

	tmp = ft_strdup("\0");
	write(p[1], var->hdc_result, ft_strlen(var->hdc_result));
	fd_bis = open(var->redir[3], O_RDONLY);
	while (read(fd_bis, buf, 1))
	{
		tmp1 = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = ft_strdup(tmp1);
		free(tmp1);
		ft_bzero(buf, 2);
	}
	write(p[1], tmp, ft_strlen(tmp));
	free(tmp);
	close(fd_bis);
}
