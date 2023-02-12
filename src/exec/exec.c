/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:17:36 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/12 18:39:45 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **create_cmd(t_token *start)
{
	char	**cmd;
	int		i;
	t_token *token;

	if (!start)
	{
		printf("No se creo");
		return (NULL);
	}
	token = start;
	//printf("Str:  %s\n", token->str);
	i = 1;
	//printf("Entra aqui\n");
	while(token && token->type < TRUNC)
	{
		//printf("str:%s\n", token->str);
		//printf("%d\n", i);
		token = token->next;
		i++;
	}
	cmd = malloc(sizeof(char *) * i);//liberar este malloc
	if(!cmd)
		return(NULL);
	token = start->next;
	cmd[0] = start->str;
	i = 1;
	while(token && token->type < TRUNC)
	{
		cmd[i] = token->str;
		token = token->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	exec_cmd(t_ms *ms, t_token *token)
{
	char **cmd;

	(void)ms;
	//printf("Va a entrar\n");
	cmd = create_cmd(token);
 	if(cmd)
	{
		//printf("%s\n", cmd[1]);
		exec_builtin(cmd, ms);
	}
	else
		printf("No se creo cmd\n"); 
}