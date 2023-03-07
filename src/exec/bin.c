/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:29:10 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/07 11:54:55 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cmd_bin(char **cmd, t_env *env, t_ms *ms)
{
	char	*path;

	if(!cmd[0])
		return (UNKNOWN_COMMAND);
	path = get_the_path(cmd[0], env);
	if(!path)
		return (UNKNOWN_COMMAND);
	if(execve(path, cmd, ms->env_bin) == -1)
	{
		ft_putstr_fd("Minishell : ", STDOUT);
		perror("execve");
	}
	return (0);
}

static int	exec_path_bin(char **cmd, t_ms *ms)
{
	if(!cmd[0])
		return (UNKNOWN_COMMAND);
	if (access(cmd[0], F_OK | X_OK) == 0)
	{
		if(execve(cmd[0], cmd, ms->env_bin) == -1)
		{
			ft_putstr_fd("Minishell : ", STDOUT);
			perror("execve");
		}
	}
	return (UNKNOWN_COMMAND);
}

int	exec_bin(char **cmd, t_env *env, t_ms *ms)
{
	int	ret;
	
	if (ft_strchr(cmd[0], '/') != 0)
	{
		ret = exec_path_bin(cmd, ms);
		if(ret == UNKNOWN_COMMAND)
		{
			ft_putstr_fd("minishell: ",STDOUT);
			perror(*cmd);
		}
	}
	else
	{
		ret = exec_cmd_bin(cmd, env, ms);
		if(ret == UNKNOWN_COMMAND)
		{
			ft_putstr_fd("minishell: ",STDOUT);
			ft_putstr_fd(*cmd,STDOUT);
			ft_putstr_fd(": command not found\n",STDOUT);
		}	
	}
	ms->parent = 0;
	printf("%d\n", ret);
	return (ret);
}

int create_children(t_ms *ms, t_env *env, char **cmd)
{
	int status;
	//int	ret;

	//ret = UNKNOWN_COMMAND;
	
	ms->pid = fork();
	if(ms->pid == -1)
		perror("fork");
	if(ms->pid == 0)
		ms->ret = exec_bin(cmd, env, ms);
	waitpid(-1, &status, 0);
	return (ms->ret);
} 