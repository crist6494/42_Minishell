/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:21:56 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/14 18:37:16 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int exec_builtin(char **cmd, t_ms * ms)
{
	int res;
	(void)ms;

	res = 0;
	//printf("Va a comparar\n");
	//printf("%s\n", );
	if(ft_strcmp(cmd[0], "echo") == 0)
		res = ft_echo(cmd);
	if(ft_strcmp(cmd[0], "pwd") == 0)
		res = ft_pwd();
	if(ft_strcmp(cmd[0], "env") == 0)
		res = ft_env(ms->env);
	if(ft_strcmp(cmd[0], "cd") == 0)
		res = ft_cd(ms, cmd);
	if(ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(ms, cmd);
	return (res);
}

