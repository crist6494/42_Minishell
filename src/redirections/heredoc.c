/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:04:50 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/20 19:53:23 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_heredoc_del(t_ms *ms, t_token *token, char *user_input)
{
	(void)ms;
	if (user_input == NULL)
	{
		return (1);
	}
	if (ft_strncmp(user_input, token->str, ft_strlen(token->str)) == 0)
		return (1);
	return (0);
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
		if (check_heredoc_del(ms, token, line) == 1)
			break ;
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	free(line);
	close(fd[1]);
	dup2(fd[0], STDIN);
	ft_close(fd[0]);
}
