/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:40:16 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/21 13:24:46 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char **args)
{
	ft_putstr_fd("minishell: ", STDOUT);
	ft_putstr_fd("cd: ", STDOUT);
	if (args[2])
		ft_putstr_fd("Too many arguments", STDOUT);
	else
	{
		ft_putstr_fd(args[1], STDOUT);
		ft_putstr_fd(": ", STDOUT);
		ft_putstr_fd(strerror(errno), STDOUT);
	}
	ft_putstr_fd("\n", STDOUT);
}

static int	update_pwd(t_env *env, int option)
{
	char	*path;
	char	*old_pwd;
	char	*pwd;

	path = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ERROR);
	old_pwd = get_env_value("PWD", env);
	if (!old_pwd)
		return (ERROR);
	if (option == 0)
		path = ft_strjoin_not_free("PWD=", pwd);
	else if (option == 1)
		path = ft_strjoin_not_free("OLDPWD=", old_pwd);
	if (!is_in_env(env, path))
		return (ERROR);
	free(pwd);
	free(old_pwd);
	ft_memdel(path);
	return (SUCCESS);
}

static int	go_to_the_path(t_env *env, int option)
{
	char	*env_path;
	int		move;

	if (option == 0)
	{
		update_pwd(env, 1);
		env_path = get_env_value("HOME", env);
		if (!env_path)
			return (ERROR);
		move = chdir(env_path);
	}
	if (option == 1)
	{
		env_path = get_env_value("OLDPWD", env);
		if (!env_path)
			return (ERROR);
		move = chdir(env_path);
		update_pwd(env, 1);
	}
	update_pwd(env, 0);
	ft_memdel(env_path);
	return (move);
}

int	ft_cd(t_ms *ms, char **cmd)
{
	int		move;
	char	*tmp;

	move = 0;
	if (!cmd[1])
		return (go_to_the_path(ms->env, 0));
	if (ft_strcmp(cmd[1], "-") == 0 && !cmd[2])
	{
		move = go_to_the_path(ms->env, 1);
		tmp = getcwd(NULL, 0);
		printf("%s\n", tmp);
		free(tmp);
	}
	else
	{
		update_pwd(ms->env, 1);
		move = chdir(cmd[1]);
		update_pwd(ms->env, 0);
		if (move != 0)
		{
			print_error(cmd);
			ms->ret = 1;
		}
	}
	return (ms->ret);
}
