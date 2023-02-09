/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmarque <anmarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:38:49 by anmarque          #+#    #+#             */
/*   Updated: 2023/02/07 11:43:32 by anmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_ms *ms)
{
	dup2(ms->in, STDIN);
	dup2(ms->out, STDOUT);
}

void	close_fds(t_ms *ms)
{
	ft_close(ms->fdin);
	ft_close(ms->fdout);
	ft_close(ms->pipin);
	ft_close(ms->pipout);
}

void	reset_fds(t_ms *ms)
{
	ms->fdin = -1;
	ms->fdout = -1;
	ms->pipin = -1;
	ms->pipout = -1;
	ms->pid = -1;
}