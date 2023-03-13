/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:17:36 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/13 12:10:35 by cmorales         ###   ########.fr       */
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

char **remove_empty_cmd(char **cmd)
{ 
	char **aux;
	int i;
	
	if (ft_strlen(cmd[0]) == 0)
	{
		i = 0;
		while (cmd[i])
			i++;
		if (i == 1)
			return (cmd);
		aux = malloc(sizeof(char *) * i);
		i = 1;
		while (cmd[i])
		{
			aux[i-1] = ft_strdup(cmd[i]);
			i++;	
		}
		aux[i-1] = '\0';
		free_tab(cmd);	
		return (aux);
	}
	return (cmd);
}

void	exec_cmd(t_ms *ms, t_token *token)
{
	char **cmd;
	int	i;

	
	if (ms->charge == 0)
		return ;
	cmd = create_cmd(ms, token);
	ms->cmds = cmd;
	i = 0;
	while (cmd && cmd[i])
    {
        cmd[i] = expansions(cmd[i], ms->env, ms->ret);
        i++;
    } 
	cmd = remove_empty_cmd(cmd);
	if (is_a_builtins(cmd[0]))
		ms->ret = exec_builtin(cmd, ms);
	else if (cmd[0])
		ms->ret = create_children(ms, ms->env, cmd);
	free_tab(cmd);
	ft_close(ms->pipin);
	ft_close(ms->pipout);
	ms->pipin = -1;
	ms->pipout = -1;
	ms->charge = 0;
}

int	ft_tokensize(t_token *token)
{
	int		size;
	t_token	*p;

	p = token;
	size = 0;
	while (p != NULL)
	{
		if (is_type(p, CMD))
			size++;
		p = p->next;
	}
	return (size);
}


void	redir_and_exec(t_ms *ms, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;
	ms->num_cmds = ft_tokensize(token);
	//printf("Numero de comandos %d\n", ms->num_cmds);
	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (is_type(prev, TRUNC))
		redir(ms, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(ms, token, APPEND);
	else if (is_type(prev, INPUT))
		input(ms, token);
	else if (is_type(prev, PIPE))
		pipe = mspipe(ms);
	else if (is_type(prev, HEREDOC))
		printf("hola soy un heredoc :)\n");
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(ms, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && ms->no_exec == 0)
    	exec_cmd(ms, token);
}