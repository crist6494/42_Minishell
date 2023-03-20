/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:29:10 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/20 18:38:51 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cmd_bin(char **cmd, t_env *env, t_ms *ms)
{
	char	*path;

	if (!cmd[0])
		return (UNKNOWN_COMMAND);
	path = get_the_path(cmd[0], env);
	if (!path)
		return (UNKNOWN_COMMAND);
	else
		execve(path, cmd, ms->env_bin);
	return (0);
}

static int	exec_path_bin(char **cmd, t_ms *ms)
{
	if (!cmd[0])
		return (UNKNOWN_COMMAND);
	if (ft_strchr(cmd[0], '/') && !cmd[0][1])
	{
		ft_putstr_fd("Minishell: ", STDERR);
		ft_putstr_fd(*cmd, STDERR);
		ft_putstr_fd(": Is a directory\n", STDERR);
		return (IS_DIRECTORY);
	}
	else if (access(cmd[0], F_OK | X_OK) == 0)
		execve(cmd[0], cmd, ms->env_bin);
	return (UNKNOWN_COMMAND);
}

int	exec_bin(char **cmd, t_env *env, t_ms *ms)
{
	if (ft_strchr(cmd[0], '/') != 0)
	{
		ms->ret = exec_path_bin(cmd, ms);
		if (ms->ret == UNKNOWN_COMMAND)
		{
			ft_putstr_fd("minishell: ", STDERR);
			perror(*cmd);
		}
	}
	else
	{
		ms->ret = exec_cmd_bin(cmd, env, ms);
		if (ms->ret == UNKNOWN_COMMAND)
		{
			ft_putstr_fd("minishell: ", STDERR);
			ft_putstr_fd(*cmd, STDERR);
			ft_putstr_fd(": command not found\n", STDERR);
		}
	}
	ms->parent = 0;
	return (ms->ret);
}

int	create_children(t_ms *ms, t_env *env, char **cmd)
{
	int	status;

	g_sig.pid = fork();
	if (g_sig.pid == -1)
		perror("fork");
	if (g_sig.pid == 0)
	{
		ms->ret = exec_bin(cmd, env, ms);
		exit(ms->ret);
	}
	else
		waitpid(g_sig.pid, &status, 0);
	ms->ret = WEXITSTATUS(status);
	if (g_sig.sigint == 1)
		return (g_sig.exit_status);
	return (ms->ret);
}
