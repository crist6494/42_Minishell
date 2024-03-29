/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:38:49 by anmarque          #+#    #+#             */
/*   Updated: 2023/03/21 13:19:15 by cmorales         ###   ########.fr       */
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
	dup2(ms->fds.dup_in, STDIN);
	dup2(ms->fds.dup_out, STDOUT);
}

void	close_fds(t_ms *ms)
{
	ft_close(ms->fds.fdin);
	ft_close(ms->fds.fdout);
	ft_close(ms->fds.pipin);
	ft_close(ms->fds.pipout);
}

void	reset_fds(t_ms *ms)
{
	ms->fds.fdin = -1;
	ms->fds.fdout = -1;
	ms->fds.pipin = -1;
	ms->fds.pipout = -1;
	ms->fds.pid = -1;
	ms->fds.heredoc_file = NULL;
}
