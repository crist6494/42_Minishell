/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:40:16 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/16 20:08:35 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_strjoin_not_free(char *s1, char *s2)
{
	char	*new;
	int		len;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = (char *)malloc(sizeof(char) * len);
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s1, len);
	ft_strlcpy(new + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	//free(s1);
	return (new);
}


static int		update_pwd(t_env *env, int option)
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
	if(option == 0)
	{
		//printf("%s\n", pwd);
		path = ft_strjoin_not_free("PWD=", pwd);
	}
	else if(option == 1)
	{
		//printf("%s\n", old_pwd);
		path = ft_strjoin_not_free("OLDPWD=", old_pwd);
	}
	is_in_env(env, path);
	//env_add(path, env);
	ft_memdel(path);
	return(SUCCESS);
} 

static int	go_to_the_path(t_env *env, int option)
{
	char	*env_path;
	int		move;
	
	if(option == 0)
	{
		update_pwd(env, 1);
		env_path = get_env_value("HOME", env);
		if(!env_path)
			return (ERROR);
		move = chdir(env_path);
	}
	if(option == 1)
	{
		env_path = get_env_value("OLDPWD", env);
		//printf("%s", env_path);
		if(!env_path)
			return (ERROR);
		move = chdir(env_path);
		update_pwd(env,  1);
	}
	update_pwd(env, 0);
	ft_memdel(env_path);
	return (move);
}

int	ft_cd(t_ms *ms, char **cmd)
{
	int	move;

	move =0;
	if(!cmd[1])
		return (go_to_the_path(ms->env, 0));
	if(ft_strcmp(cmd[1], "-") == 0)
		move = go_to_the_path(ms->env, 1);
	 else
	{
		update_pwd(ms->env, 1);
		move = chdir(cmd[1]);
		update_pwd(ms->env, 0);
	} 
	return (move);
}