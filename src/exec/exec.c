/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:17:36 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/23 20:26:40 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_cmd(t_ms *ms, t_token *start)
{
	char	**cmd;
	int		i;
	t_token	*token;
	(void)ms;
	if (!start)
		return (NULL);
	token = start;
	i = 0;
	while (token && token->type < TRUNC)
	{
		//printf("%d\n", i);
		token = token->next;
		i++;
	}
	ms->num_cmds = i;
	cmd = malloc(sizeof(char *) * (i + 1)); //liberar este malloc
	if (!cmd)
		return (NULL);
	token = start->next;
	cmd[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
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

	//printf("Va a entrar\n");
	cmd = create_cmd(ms, token);
	if (is_a_builtins(cmd[0]))
		ms->ret = exec_builtin(cmd, ms);
	else if (cmd[0])
		ms->ret = exec_bin(cmd, ms->env, ms);
	free(cmd);
}