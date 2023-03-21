/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:17:36 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/21 13:35:32 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**malloc_cmd(t_token *token, char **cmd, int i)
{
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	return (cmd);
}

static char	**create_cmd(t_token *start)
{
	char	**cmd;
	int		i;
	t_token	*token;

	cmd = NULL;
	if (!start)
		return (NULL);
	token = start;
	i = 0;
	cmd = malloc_cmd(token, cmd, i);
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

static char	**remove_empty_cmd(char **cmd)
{
	char	**aux;
	int		i;

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
			aux[i - 1] = ft_strdup(cmd[i]);
			i++;
		}
		aux[i - 1] = NULL;
		free_tab(cmd);
		return (aux);
	}
	return (cmd);
}

void	redir_and_exec(t_ms *ms, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (is_type(prev, TRUNC))
		redir(ms, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(ms, token, APPEND);
	else if (is_type(prev, INPUT))
		input(ms, token);
	else if (is_type(token, HEREDOC) || is_type(prev, HEREDOC))
		heredoc(ms, token);
	else if (is_type(prev, PIPE))
		pipe = mspipe(ms);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(ms, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev) && pipe != 1
		&& ms->no_exec == 0)
		exec_cmd(ms, token);
}

void	exec_cmd(t_ms *ms, t_token *token)
{
	char	**cmd;
	int		i;

	if (ms->charge == 0)
		return ;
	cmd = create_cmd(token);
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
	ft_close(ms->fds.pipin);
	ft_close(ms->fds.pipout);
	ms->charge = 0;
}
