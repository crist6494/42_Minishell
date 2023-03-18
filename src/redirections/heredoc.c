/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:04:50 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/18 19:30:02 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_heredoc_del(t_ms *ms, t_token *token, char *user_input)
{
	(void)ms;
	if(user_input == NULL)
	{
		//ft_putstr_fd("minishell: ",STDERR);
		//ft_putstr_fd("end-of-file: expected\n",STDERR);
		return (1);
	}
	
	if(ft_strncmp(user_input, token->str, ft_strlen(token->str)) == 0)
		return (1);
	return (0);
}

int heredoc(t_ms *ms, t_token *token)
{
	int		fd[2];
	char	*line;

	ms->fds.act_heredoc = 1;
	fd[0] = open(ms->fds.heredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipe(fd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		//printf("%s\n", line);
		//expansions(line, ms->env, ms->ret);
		if(check_heredoc_del(ms, token, line) == 1)
			break;
		//expansions(env)
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}