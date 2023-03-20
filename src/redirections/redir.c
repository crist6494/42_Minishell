/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmarque <anmarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 01:53:43 by anmarque          #+#    #+#             */
/*   Updated: 2023/03/20 14:45:23 by anmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir(t_ms *ms, t_token *token, int type)
{
	if (type == TRUNC)
		ms->fds.fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		ms->fds.fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (ms->fds.fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		ms->ret = 1;
		ms->no_exec = 1;
		return ;
	}
	dup2(ms->fds.fdout, STDOUT);
	ft_close(ms->fds.fdout);
}

void	input(t_ms *ms, t_token *token)
{
	ms->fds.fdin = open(token->str, O_RDONLY);
	if (ms->fds.fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		ms->ret = 1;
		ms->no_exec = 1;
		return ;
	}
	dup2(ms->fds.fdin, STDIN);
	ft_close(ms->fds.fdin);
}
