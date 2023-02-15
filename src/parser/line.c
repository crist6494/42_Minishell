/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:00:16 by anmarque          #+#    #+#             */
/*   Updated: 2023/02/15 20:02:58 by cmorales         ###   ########.fr       */
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
	if (!(new = malloc(sizeof(char) * (i + 2 * count + 1))))
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
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

int		quote_check(t_ms *ms, char **line)
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

void	ft_print_path(void)
{
	char	*working_dir;

	write(1, "\n,",1);
	working_dir = getcwd(NULL, 0);
	ft_putstr_fd(BLUE, 1);
	ft_putstr_fd(working_dir, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd("\001\033[0;39m\002", 1);
	free(working_dir);
}

void	parse(t_ms *ms)
{
	char	*line;
	t_token	*token;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	ft_print_path();
	line = readline("\033[1;32mms42> \033[0m");
	if (!line && (ms->exit = 1))
	{
		ft_putendl_fd("exit", STDOUT);
		return;
	}
	add_history(line);
	if (g_sig.sigint == 1)
		ms->ret = g_sig.exit_status;
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
