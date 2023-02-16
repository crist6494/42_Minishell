/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmarque <anmarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:42:14 by anmarque          #+#    #+#             */
/*   Updated: 2023/02/15 10:13:14 by anmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_ms *ms, t_env *env)
{
	if (ms->env == env && env->next == NULL)
	{
		ft_memdel(ms->env->value);
		ms->env->value = NULL;
		ms->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	ft_unset(char **args, t_ms *ms)
{
	t_env	*env;
	t_env	*tmp;
    int     i;

    i = 1;
    while (args[i])
	{
        env = ms->env;
	
        if (ft_strncmp(args[i], env->value, env_size(env->value)) == 0)
        {
            if (env->next)
                ms->env = env->next;
            free_node(ms, env);
            i++;
            continue;
        }
        while (env && env->next)
        {
            if (ft_strncmp(args[i], env->next->value, env_size(env->next->value)) == 0)
            {
                tmp = env->next->next;
                free_node(ms, env->next);
                env->next = tmp;
                break;
            }
            env = env->next;
        }
        i++;
    }
	return (SUCCESS);
}
