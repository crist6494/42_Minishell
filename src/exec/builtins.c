/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:21:56 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/23 20:20:56 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	is_a_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **cmd, t_ms *ms)
{
	int	res;

	res = 0;
	if (ft_strcmp(cmd[0], "echo") == 0)
		res = ft_echo(cmd);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		res = ft_pwd();
	if (ft_strcmp(cmd[0], "env") == 0)
		res = ft_env(ms->env);
	if (ft_strcmp(cmd[0], "export") == 0)
		res = ft_export(cmd, ms->env, ms->secret_env);
	if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(cmd, ms);
	if (ft_strcmp(cmd[0], "cd") == 0)
		res = ft_cd(ms, cmd);
	if (ft_strcmp(cmd[0], "exit") == 0)
		res = ft_exit(ms, cmd);
	if (ft_strcmp(cmd[0], "path") == 0)
		ft_all_the_paths(ms->env);
	return (res);
}
