/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gift_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:16:29 by ggane             #+#    #+#             */
/*   Updated: 2017/04/21 18:01:35 by ggane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	ft_pid_null(t_var *var, char ***cmd, int *fd_in, int p[2])
{
	(var->from == 1 && var->to == 2) ? *(cmd + 1) = NULL : (0);
	(var->from != 0) ? *fd_in = var->from : dup2(*fd_in, 0);
	if (*(cmd + 1) != NULL)
		(var->from && var->from != var->to) ? dup2(p[1], var->from) :
			dup2(p[1], 1);
	close(p[0]);
	var->repeat = 0;
	if ((!var->hdc || (var->hdc && var->numredir == 0)) && !(var->hdc == 1 &&
	var->numredir == 0 && var->truc))
	{
		ft_exec(*cmd, var);
		exit(EXIT_FAILURE);
	}
	else
	{
		if ((var->hdc && var->hdc_result != NULL && var->numredir != 0) ||
		(var->hdc == 1 && var->numredir == 0 && var->truc))
			ft_pid_rep(var, p);
		else if (var->hdc && var->redir[2][0] == '<')
			ft_heredoc_pipe(var, p);
		else if (var->hdc)
			ft_hdc_pipe(var, p);
		var->hdc = 0;
	}
	exit(EXIT_FAILURE);
}

void	ft_pid_positif(t_var *var, int p[2], int *fd_in, char ****cmd)
{
	if (var->oui == 1)
	{
		close(STDERR_FILENO);
		dup2(var->old_stderr, STDERR_FILENO);
		close(var->old_stderr);
		dup2(STDOUT_FILENO, STDIN_FILENO);
	}
	if (var->red == 1 || var->red == 2)
		dup2(0, var->red);
	else
		dup2(STDOUT_FILENO, STDIN_FILENO);
	var->red = 0;
	close(p[1]);
	*fd_in = p[0];
	(*cmd)++;
}

void	ft_init_loopipe(int *j, int *status, int *fd_in)
{
	*j = 0;
	*status = 0;
	*fd_in = 0;
}

int		loop_pipe2(char ***cmd, t_var *var)
{
	int		p[2];
	pid_t	pid;
	int		fd_in;
	int		status;
	int		j;

	ft_init_loopipe(&j, &status, &fd_in);
	while (*cmd != NULL)
	{
		ft_loop_red(var, j, cmd);
		pipe(p);
		pid = fork();
		if (pid > 0 && *(cmd + 1) == NULL)
		{
			waitpid(pid, &status, 0);
			wait(&status);
		}
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			ft_pid_null(var, cmd, &fd_in, p);
		else if (++j > -2)
			ft_pid_positif(var, p, &fd_in, &cmd);
	}
	return (status);
}

int		gift_pipe(t_var *term)
{
	int		j;
	int		ret;
	char	***cmd;
	int		i;

	cmd = (char ***)malloc(sizeof(char **) * (count_tab(term->pipe) + 1));
	i = -1;
	while (term->pipe[++i])
		cmd[i] = split_qte(term->pipe[i]);
	cmd[i] = NULL;
	j = 0;
	init_std(term);
	ret = loop_pipe2(cmd, term);
	init_termios(term);
	i = -1;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
			free(cmd[i][j]);
		free(cmd[i]);
	}
	free(cmd);
	ft_freetab(&(term->pipe));
	return (ret);
}
