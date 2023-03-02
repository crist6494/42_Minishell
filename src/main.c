/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:57:13 by anmarque          #+#    #+#             */
/*   Updated: 2023/03/02 14:18:24 by cmorales         ###   ########.fr       */
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
	//printf("Redir\n");
	if (is_type(prev, TRUNC))
		redir(ms, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(ms, token, APPEND);
	else if (is_type(prev, INPUT))
		input(ms, token);
	else if (is_type(prev, PIPE))
		pipe = mspipe(ms);
	else if (is_type(prev, HEREDOC))
		printf("hola\n");
	//printf("pipe es %d\n", pipe);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(ms, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && ms->no_exec == 0)
    	exec_cmd(ms, token);
}

void ft_void()
{
	system("leaks -q minishell"); //Mirar procesos cuando sale
}

void	minishell(t_ms *ms)
{
	t_token	*token;
	int		status;

	// IMPRIMO LOS TOKENS PARA VER QUE LO HE PARSEADO BIEN. BORRAR
	//print_tokens(ms->start);
	//atexit(ft_void);
	token = next_run(ms->start, NOSKIP);
	if (is_types(ms->start, "TAI")) 
		token = ms->start->next;
	while (ms->exit == 0 && token)
	{
		ms->charge = 1;
		ms->parent = 1;
		ms->last = 1;
		redir_and_exec(ms, token);
		reset_std(ms);
		close_fds(ms);
		reset_fds(ms);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (ms->last == 0)
			ms->last = status;
		else
			ms->last = ms->ret;
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
	while (ms.exit == 0)
	{
		sig_init();
		ms.start = NULL;
		reset_std(&ms);
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

