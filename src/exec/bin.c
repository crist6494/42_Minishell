/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:29:10 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/23 00:20:50 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_all_the_paths(t_env *env)
{
	char	*paths;
	char	**all_paths;

	if(!env)
		return (NULL);
	paths = get_env_value("PATH", env);
	all_paths = ft_split(paths, ':');
	return (all_paths);
}

char	*get_the_path(char *cmd, t_env *env)
{
	char	**all_paths;
	char	*path;
	char	*slash;
	int		i;

	i = 0;
	all_paths = ft_all_the_paths(env);
	while(all_paths[i])
	{
		slash = ft_strjoin_not_free(all_paths[i], "/");
		path = ft_strjoin_not_free(slash, cmd);
		free(slash);
		if(access(path,F_OK | X_OK) == 0)
		{
			free_tab(all_paths);
			//printf("%s", path);
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(all_paths);
	return (NULL);
}

int	exec_bin(char **cmd, t_env *env, t_ms *ms)
{
	char	*path;
	int		status;
	pid_t	pid;
	pid = fork();

	if(pid == -1)
		return (ERROR);
	if(pid == 0)
	{
		path = get_the_path(cmd[0], env);
		if (cmd[0] && path)
		{
			execve(path, cmd, ms->env_bin);
			free(path);
		}
		else
			perror(cmd[0]);
	}
	else
		waitpid(-1, &status, 0);
	return (1);
}