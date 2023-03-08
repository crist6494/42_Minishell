/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:57:13 by anmarque          #+#    #+#             */
/*   Updated: 2023/03/08 11:20:16 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;


void	minishell(t_ms *ms)
{
	t_token	*token;
	int		status;

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

/* static int check_input(t_ms *ms, int ac, char **av)
{
	if(ac != 1 && ac != 3)
		return (usage_message(ms, 0));
	if(ac == 3)
	{
		if(!av[1] || (av[1] && ft_strcmp(av[1], "-c") != 0))
			return (usage_message(ms, 0));
		else if (!av[2] || (av[2] && av[2][0] == '\0'))
			return (usage_message(ms, 0));
	}
	else
		ms->iterative = 1;
	return (1);
} */
