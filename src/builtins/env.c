/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:49:48 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/18 18:20:40 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_env(t_env *env, char **cmd)
{
	if(!env)
		return (ERROR);
	if(cmd[0] && cmd[1])
	{
		ft_putstr_fd("Minishell: env: ", STDERR);
		ft_putendl_fd("too many arguments", STDERR);
		return (ERROR);
	}
	while(env && env->next)
	{
		if(ft_strchr(env->value, '='))
			ft_putendl_fd(env->value, STDOUT);
		env = env->next;
	}
	return(SUCCESS);
}