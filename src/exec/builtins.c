/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:21:56 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/12 19:54:19 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int exec_builtin(char **argv, t_ms * ms)
{
	int res;
	(void)ms;

	res = 0;
	//printf("Va a comparar\n");
	//printf("%s\n", );
	if(ft_strcmp(argv[0], "echo") == 0)
		res = ft_echo(argv);
	if(ft_strcmp(argv[0], "pwd") == 0)
		res = ft_pwd();
	if(ft_strcmp(argv[0], "env") == 0)
		res = ft_env(ms->env);
	return (res);
}