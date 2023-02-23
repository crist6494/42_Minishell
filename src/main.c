/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:57:13 by anmarque          #+#    #+#             */
/*   Updated: 2023/02/23 12:39:53 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

void	redir_and_exec(t_ms *ms, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	//(void)next;
	if (is_type(prev, TRUNC))
		printf("TODO\n");
		//redir(ms, token, TRUNC);
	else if (is_type(prev, APPEND))
		printf("TODO\n");
		//redir(ms, token, APPEND);
	else if (is_type(prev, INPUT))
		printf("TODO\n");
		//input(ms, token);
	else if (is_type(prev, PIPE))
		printf("TODO\n");
		//pipe = mspipe(ms);
	if (next && is_type(next, END) == 0 && pipe != 1)
		//printf("TODO REDIR AND EXEC CMD %s\n", next->next->str);
		//redir_and_exec(ms, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && ms->no_exec == 0)
		printf("holaaaa\n");
    	//exec_cmd(ms, token);
		/* {
			while(token)
			{
				printf("%s\n",token->str);
				token = token->next;	
			}
		} */
        //printf("TODO: EXECUTE CMD %s\n", token->str);
}

void	minishell(t_ms *ms)
{
	t_token	*token;
	int		status;

	// IMPRIMO LOS TOKENS PARA VER QUE LO HE PARSEADO BIEN. BORRAR
	//print_tokens(ms->start);
	token = next_run(ms->start, NOSKIP);
	if (is_types(ms->start, "TAI")) 
		token = ms->start->next;
	while (ms->exit == 0 && token)
	{
		ms->charge = 1;
		ms->parent = 1;
		ms->last = 1;
		redir_and_exec(ms, token);
		//printf("holaaaa\n");
		reset_std(ms);
		close_fds(ms);
		reset_fds(ms);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		ms->ret = (ms->last == 0) ? status : ms->ret;
		if (ms->parent == 0)
		{
			free_token(ms->start);
			exit(ms->ret);
		}
		ms->no_exec = 0;
		token = next_run(token, SKIP);
	}
}

int		main(int ac, char **av, char **env)
{
	t_ms	ms;

	(void)ac;
	(void)av;
	ms.in = dup(STDIN);
	ms.out = dup(STDOUT);
	ms.exit = 0;
	ms.ret = 0;
	ms.no_exec = 0;
	ms.env_bin = env;
	reset_fds(&ms);
	env_init(&ms, env);
	secret_env_init(&ms, env);
	//printf("%s", get_env_name("HOME", ms.env));
	//increment_shell_level(ms.env);
	while (ms.exit == 0)
	{
		sig_init();
		ms.start = NULL;
		parse(&ms);
		if (ms.start != NULL && check_line(&ms, ms.start))
			minishell(&ms);
		if (ms.start)
			free_token(ms.start);
	}
	free_env(ms.env);
	free_env(ms.secret_env);
	return (ms.ret);
}

