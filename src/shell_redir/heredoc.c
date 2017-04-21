/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:51:24 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 17:41:49 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		ft_multiple_opt(char **text, t_var *term, int *j)
{
	if ((*text = loop_init_heredoc(term, j)) == NULL)
	{
		free(term->tmp);
		return (0);
	}
	if (!ft_strcmp(term->redir[2], ">") || !ft_strcmp(term->redir[2], ">>"))
	{
		term->truc = 1;
		redir_out(term, j);
	}
	return (5);
}

void	ft_hdc_out(t_var *term, int fd_tab[2], char *text)
{
	int		fd;
	int		fd_bis;
	char	buf[2];
	char	*tmp;

	tmp = ft_strdup("\0");
	close(fd_tab[0]);
	if (!ft_strcmp(term->redir[4], ">>"))
		fd = open(term->redir[5], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(term->redir[5], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, text, ft_strlen(text));
	if (!ft_strcmp(term->redir[2], "<"))
	{
		fd_bis = open(term->redir[3], O_RDONLY);
		while (read(fd_bis, buf, 1))
		{
			tmp = ft_strjoin(tmp, buf);
			ft_bzero(buf, 2);
		}
		write(fd, tmp, ft_strlen(tmp));
		close(fd_bis);
		close(fd);
	}
}

void	ft_hdc_read(t_var *term, int fd_tab[2])
{
	int		fd;
	char	buf[2];
	char	*tmp;

	tmp = ft_strdup("\0");
	fd = open(term->redir[3], O_RDONLY);
	while (read(fd, buf, 1))
	{
		tmp = ft_strjoin(tmp, buf);
		ft_bzero(buf, 2);
	}
	ft_putstr_fd(tmp, fd_tab[1]);
	close(fd);
}

void	ft_pid_null_hdc(t_var *term, int fd_tab[2], char *text)
{
	if (!ft_strcmp(term->redir[4], ">") || (!ft_strcmp(term->redir[4], ">>")))
		ft_hdc_out(term, fd_tab, text);
	else
	{
		dup2(fd_tab[1], STDOUT_FILENO);
		close(fd_tab[0]);
		ft_putstr_fd(text, fd_tab[1]);
		if (!ft_strcmp(term->redir[2], "<"))
			ft_hdc_read(term, fd_tab);
		exit(0);
	}
	exit(0);
}

int		heredoc(t_var *term, int *j)
{
	pid_t	pid;
	char	*text;
	int		fd_tab[2];
	int		status;

	ft_init_heredoc(term);
	if (ft_multiple_opt(&text, term, j) == 0)
		return (0);
	if (!term->hdc || ((term->hdc && term->numredir == 0) && term->truc == 0))
	{
		pipe(fd_tab);
		((pid = fork()) > 0) ? waitpid(-1, &status, 0) : (0);
		(pid == 0) ? ft_pid_null_hdc(term, fd_tab, text) : (0);
		dup2(fd_tab[0], STDIN_FILENO);
		term->red = fd_tab[0];
		term->her = fd_tab[1];
		close(fd_tab[1]);
		return (1);
	}
	else
	{
		term->hdc_result = ft_strdup(text);
		free(text);
	}
	return (1);
}
