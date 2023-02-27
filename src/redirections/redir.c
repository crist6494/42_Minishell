/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 01:53:43 by anmarque          #+#    #+#             */
/*   Updated: 2023/02/27 20:31:19 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir(t_ms *ms, t_token *token, int type)
{
	if (type == TRUNC)
		ms->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		ms->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (ms->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		ms->ret = 1;
		ms->no_exec = 1;
		return ;
	}
	dup2(ms->fdout, STDOUT);
	ft_close(ms->fdout);
}

void	input(t_ms *ms, t_token *token)
{
	ms->fdin = open(token->str, O_RDONLY);
	if (ms->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		ms->ret = 1;
		ms->no_exec = 1;
		return ;
	}
	dup2(ms->fdin, STDIN);
	ft_close(ms->fdin);
}

int		mspipe(t_ms *ms)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		ms->pipin = pipefd[0];
		ms->pid = -1;
		ms->parent = 0;
		ms->no_exec = 0;
		return (2);
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		ms->pipout = pipefd[1];
		ms->pid = pid;
		ms->last = 0;
		return (1);
	}
}
 