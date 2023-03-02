/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:17:36 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/02 13:45:51 by cmorales         ###   ########.fr       */
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
		token = token->next;
		i++;
	}
	ms->num_cmds = i;
	cmd = malloc(sizeof(char *) * (i + 1));
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
	int	i;

	if (ms->charge == 0)
		return ;
	cmd = create_cmd(ms, token);
	i = 0;
	while (cmd && cmd[i])
    {
        cmd[i] = expansions(cmd[i], ms->env, ms->ret);
        i++;
    } 
	if (is_a_builtins(cmd[0]))
		ms->ret = exec_builtin(cmd, ms);
	else if (cmd[0])
		ms->ret = exec_bin(cmd, ms->env, ms);
	free_tab(cmd);
	ft_close(ms->pipin);
	ft_close(ms->pipout);
	ms->pipin = -1;
	ms->pipout = -1;
	ms->charge = 0;
}