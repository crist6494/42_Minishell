/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:15:31 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/06 18:42:02 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_all_the_paths(t_env *env)
{
	char	*paths;
	char	**all_paths;
	//int i = 0;

	if(!env)
		return (NULL);
	paths = get_env_value("PATH", env);
	all_paths = ft_split(paths, ':');
	free(paths);
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
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(all_paths);
	return (NULL);
}