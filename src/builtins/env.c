/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:49:48 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/14 11:22:18 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_env(t_env *env)
{
	if(!env)
		return (ERROR);
	while(env && env->next)
	{
		if(ft_strchr(env->value, '='))
			ft_putendl_fd(env->value, STDOUT);
		env = env->next;
	}
	return(SUCCESS);
}