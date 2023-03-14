/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:04:50 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/14 12:32:46 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_ms *ms, t_token *token)
{
	(void)ms;
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (-1);
	line = readline("> ");
	printf("line: %s\n", token->str);
	while (ft_strncmp(line, token->str, ft_strlen(line) + 1))
	{
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}