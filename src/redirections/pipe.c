/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:38:37 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/07 20:10:24 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		mspipe(t_ms *ms)
{
	ms->pipe = 1;
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		//printf("En es el proceso hijo\n");
		ft_close(fd[1]);
		dup2(fd[0], STDIN);
		ms->pipin = fd[0];
		ms->pid = -1;
		ms->parent = 0;
		ms->no_exec = 0;
		return (2);
	}
	else
	{
		//printf("Estoy en el proceso padre\n");
		ft_close(fd[0]);
		dup2(fd[1], STDOUT);
		ms->pipout = fd[1];
		ms->pid = pid;
		ms->last = 0;
		return (1);
	}
}