/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:19:33 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/16 11:33:46 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home(t_env *env)
{
	char	*home;
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if(!pwd)
		return (NULL);
	home = get_env_value("HOME", env);
	if(home && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		tmp = pwd;
		pwd = ft_strjoin_not_free("~", &pwd[ft_strlen(home)]);
		free(tmp);
	}
	free(home);
	home = ft_strjoin_not_free(BLUE, pwd);
	free(pwd);
	pwd = ft_strjoin_not_free(home, " ");
	free(home);
	home = ft_strjoin_not_free(pwd, DEFAULT);
	free(pwd);
	return (home);
}

char	*get_promt(t_env *env)
{
	char	*home;
	char	*promt;
	
	home = get_home(env);
	promt = ft_strjoin_not_free(home, "\033[1;32mms42> \033[0m");
	free(home);
	return (promt);
}