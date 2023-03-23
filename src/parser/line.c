/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:00:16 by anmarque          #+#    #+#             */
/*   Updated: 2023/03/23 11:48:07 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*space_alloc(char *line)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(line, i))
			count++;
		i++;
	}
	new = malloc(sizeof(char) * (i + 2 * count + 1));
	if (!new)
		return (NULL);
	return (new);
}

char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_sep(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '<')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	return (new[j] = '\0', ft_memdel(line), new);
}

int	quote_check(t_ms *ms, char **line)
{
	if (quotes(*line, 2147483647))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		ft_memdel(*line);
		ms->ret = 2;
		ms->start = NULL;
		return (1);
	}
	return (0);
}

void	parse2(t_ms *ms, char *line)
{
	t_token	*token;

	if (ft_strlen(line) > 0)
		add_history(line);
	if (line && quote_check(ms, &line))
		return ;
	line = space_line(line);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	ms->start = get_tokens(line);
	ft_memdel(line);
	squish_args(ms);
	token = ms->start;
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0);
		token = token->next;
	}
}

void	parse(t_ms *ms)
{
	char	*line;
	char	*prompt;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, SIG_IGN);
	prompt = get_promt(ms->env);
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		ms->exit = 1;
		ft_putendl_fd("exit", STDERR);
		return ;
	}
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
	{
		ms->ret = g_sig.exit_status;
		g_sig.sigquit = 0;
	}
	parse2(ms, line);
}
