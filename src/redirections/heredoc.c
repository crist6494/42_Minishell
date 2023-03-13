/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:04:50 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/13 20:53:31 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_ms *ms, t_token *token)
{
	(void)ms;
	int		fdpipe[2];
	char	*line;

	if (pipe(fdpipe) < 0)
		return (-1);
	line = readline("> ");
	//printf("line: %s\n", token->str);
	while (ft_strncmp(line, token->str, ft_strlen(line) + 1))
	{
		ft_putstr_fd(line, fdpipe[1]);
		ft_putstr_fd("\n", fdpipe[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fdpipe[1]);
	return (fdpipe[0]);
}