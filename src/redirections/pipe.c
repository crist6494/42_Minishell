/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:38:37 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/15 20:41:18 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int		mspipe(t_ms *ms)
{
	pid_t	pid;
	int		fd[2];
	//int status;

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
		//if(ms->fds.act_heredoc == 1)
			//waitpid(pid, NULL, 0); //preguntar si es necesario
		ft_close(fd[0]);
		dup2(fd[1], STDOUT);
		ms->fds.pipout = fd[1];
		ms->fds.pid = pid;
		ms->last = 0;
		//ms->ret = WEXITSTATUS(status);
		return (1);
	}
}

/*int	**init_pipes(int n_cmds)
{
	int **pipes;
	int i;

	if(n_cmds == 1)
		return (0);
	pipes = ft_calloc(n_cmds - 1, sizeof(int *));
	i = 0;
	while (i < n_cmds - 1)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}*/
