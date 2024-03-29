/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:38:37 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/21 13:18:58 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	mspipe(t_ms *ms)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(fd[1]);
		dup2(fd[0], STDIN);
		ms->fds.pipin = fd[0];
		ms->fds.pid = -1;
		ms->parent = 0;
		ms->no_exec = 0;
		return (2);
	}
	else
	{
		dup2(fd[1], STDOUT);
		ft_close(fd[0]);
		ms->fds.pipout = fd[1];
		ms->fds.pid = pid;
		ms->last = 0;
		return (1);
	}
}
