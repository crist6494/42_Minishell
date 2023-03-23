/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:57:13 by anmarque          #+#    #+#             */
/*   Updated: 2023/03/23 11:32:25 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

void	init_ms2(t_ms *ms, t_token *token)
{
	ms->charge = 1;
	ms->parent = 1;
	ms->last = 1;
	signal(SIGQUIT, &sig_quit);
	redir_and_exec(ms, token);
	reset_std(ms);
	close_fds(ms);
	reset_fds(ms);
}

void	minishell(t_ms *ms)
{
	t_token	*token;
	int		status;

	token = next_run(ms->start, NOSKIP);
	if (is_types(ms->start, "TAIH"))
		token = ms->start->next;
	while (ms->exit == 0 && token)
	{
		init_ms2(ms, token);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (ms->last == 0)
			ms->ret = status;
		if (ms->parent == 0)
		{
			free_token(ms->start);
			exit(ms->ret);
		}
		ms->no_exec = 0;
		token = next_run(token, SKIP);
	}
}

void	init_ms(t_ms *ms, char **env)
{
	ms->fds.dup_in = dup(STDIN);
	ms->fds.dup_out = dup(STDOUT);
	ms->exit = 0;
	ms->ret = 0;
	ms->no_exec = 0;
	ms->env_bin = env;
}

int	main(int ac, char **av, char **env)
{
	t_ms	ms;

	(void)ac;
	(void)av;
	init_ms(&ms, env);
	reset_fds(&ms);
	env_init(&ms, env);
	secret_env_init(&ms, env);
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
