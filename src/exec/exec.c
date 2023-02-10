/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:17:36 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/10 20:36:52 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **create_cmd(t_token *start)
{
	char	**cmd;
	int		i;
	t_token *token;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while(token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	cmd = malloc(sizeof(char *) * i);//liberar este malloc
	if(!cmd)
		return(NULL);
	i = 1;
	while(token && token->type < TRUNC)
	{
		cmd[i] = token->str;
		token = token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

int exec_builtin(char **argv, t_ms * ms)
{
	int res;
	(void)ms;

	res = 0;
	printf("Hola\n");
	printf("%s\n", argv[0]);
	if(ft_strcmp(argv[0], "echo") == 0)
		res = ft_echo_builtin(argv);
	return (res);
}

void	exec_cmd(t_ms *ms, t_token *token)
{
	char **cmd;

	(void)token;
	cmd = create_cmd(token);
	if(cmd)
	{
		printf("add\n");
		ms->ret = exec_builtin(cmd, ms);
	}
	else
		printf("Hola\n");
}