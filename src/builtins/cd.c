/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:40:16 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/14 20:30:19 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*get_env_value(char *arg, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->value)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(arg, env_name) == 0)
		{
			ft_memdel(env_val);
			env_val = env_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}*/

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
		return (ERROR);
	//printf("PWD: %s\n", buf_cwd);
	//printf("Entra aqui\n");
	oldpwd = ft_strjoin2("OLPWD=", buf_cwd);
	if(is_in_env(env, oldpwd))
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	return(SUCCESS);
} 

static int	go_to_the_path(t_env *env)
{
	char	*env_path;
	int		move;
	
	update_pwd(env);
	env_path = get_env_value("HOME", env);	
	move = chdir(env_path);
	return (move);
}

int	ft_cd(t_ms *ms, char **cmd)
{
	(void)cmd;
	update_pwd(ms->env);
	//printf("%s", get_env_value("PWD",ms->env));
	if(!cmd[1])
		go_to_the_path(ms->env);
	else
		chdir("/Users/cmorales/Downloads");
	return (SUCCESS);
}