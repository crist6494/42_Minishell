/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:40:16 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/15 19:37:52 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_strjoin2(char *s1, char *s2)
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


static int		update_pwd(t_env *env)
{
	char	*buf_cwd;
	char	*oldpwd;

	(void)env;
	buf_cwd = getcwd(NULL, 0);
	if (!buf_cwd)
		return (ERROR);;
	oldpwd = ft_strjoin2("OLDPWD=", buf_cwd);
	if(is_in_env(env, oldpwd))
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	return(SUCCESS);
} 

static int	go_to_the_path(t_env *env, int option)
{
	char	*env_path;
	int		move;
	
	if(option == 0)
	{
		update_pwd(env);
		env_path = get_env_value("HOME", env);
		if(!env_path)
			return (ERROR);
		move = chdir(env_path);
	}
	if(option == 1)
	{
		update_pwd(env);
		env_path = get_env_value("OLDPWD", env);
		if(!env_path)
			return (ERROR);
		move = chdir(env_path);
	}
	ft_memdel(env_path);
	return (move);
}

int	ft_cd(t_ms *ms, char **cmd)
{
	int	move;

	if(!cmd[1])
		return (go_to_the_path(ms->env,0));
	if(ft_strcmp(cmd[1], "-") == 0)
		move = go_to_the_path(ms->env, 1);
	else
	{
		update_pwd(ms->env);
		move = chdir(cmd[1]);
	}
	return (move);
}