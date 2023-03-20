/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmarque <anmarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:11:03 by anmarque          #+#    #+#             */
/*   Updated: 2023/03/20 15:04:21 by anmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(int error, const char *arg)
{
	int	i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	print_and_success(t_env *env)
{
	print_sorted_env(env);
	return (SUCCESS);
}

int	ft_export(char **args, t_env *env, t_env *secret)
{
	int	error_ret;
	int	i;

	if (!args[1])
		return (print_and_success(env));
	else
	{
		i = 1;
		while (args[i])
		{
			error_ret = is_valid_env(args[i]);
			if (args[i][0] == '=')
				error_ret = -3;
			if (error_ret <= 0)
				print_error(error_ret, args[i]);
			else if (is_in_env(env, args[i]) == 0)
			{
				env_add(args[i], env);
				env_add(args[i], secret);
			}
			i++;
		}
	}
	return (SUCCESS);
}
