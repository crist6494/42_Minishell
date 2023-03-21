/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:04:50 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/21 13:28:27 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_heredoc_del(t_token *token, char *user_input)
{
	int	tlen;
	int	ulen;

	if (user_input == NULL)
	{
		return (1);
	}
	ulen = ft_strlen(user_input);
	tlen = ft_strlen(token->str);
	if (ulen == tlen && ft_strncmp(user_input, token->str, tlen) == 0)
		return (1);
	return (0);
}

static char	*get_word(char *line, int i, int j)
{
	char	*word;
	int		k;

	word = malloc(sizeof(char) * (j - i + 1));
	if (!word)
		return (NULL);
	k = 0;
	while (i != j)
	{
		word[k] = line[i];
		k++;
		i++;
	}
	word[k] = '\0';
	return (word);
}

static void	write_env_if_exists(t_ms *ms, char *var, int fd)
{
	char	*new_var;
	int		j;

	new_var = get_env_value(var, ms->env);
	j = 0;
	while (new_var[j])
		write(fd, &new_var[j++], 1);
	free(new_var);
}

static void	write_line_heredoc(t_ms *ms, char *line, int fd)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (line[i])
	{
		if (line[i] != '$')
			write(fd, &line[i++], 1);
		else
		{
			j = ++i;
			while (ft_isalnum(line[j]))
				j++;
			if (i == j)
				return ;
			var = get_word(line, i, j);
			write_env_if_exists(ms, var, fd);
			i = j;
			free(var);
		}
	}
}

void	heredoc(t_ms *ms, t_token *token)
{
	int		fd[2];
	char	*line;

	fd[0] = open(ms->fds.heredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipe(fd) < 0)
		return ;
	while (1)
	{
		line = readline("> ");
		if (check_heredoc_del(token, line) == 1)
			break ;
		write_line_heredoc(ms, line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	free(line);
	close(fd[1]);
	dup2(fd[0], STDIN);
	ft_close(fd[0]);
}
