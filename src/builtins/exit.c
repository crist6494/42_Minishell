/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmarque <anmarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:23:29 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/20 13:56:28 by anmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	ft_check_digit(char *str)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = FALSE;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			has_digit = TRUE;
		else
			break ;
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0' && has_digit == TRUE)
		return (TRUE);
	else
		return (FALSE);
}

static int	has_error(char **cmd, int i, t_ms *ms)
{
	if (errno || ft_check_digit(cmd[i]) == FALSE)
	{
		ft_putstr_fd("Minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[i], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
		return (255);
	}
	if (cmd[i + 1])
	{
		ft_putstr_fd("Minishell: exit: ", STDERR);
		ft_putendl_fd("too many arguments", STDERR);
		ms->exit = 0;
		return (TRUE);
	}
	return (FALSE);
}

int	ft_exit(t_ms *ms, char **cmd)
{
	int	i;

	i = 1;
	ms->exit = 1;
	ft_putendl_fd("exit", STDERR);
	if (cmd[i] && ft_strcmp(cmd[i], "--") == 0)
		i++;
	if (cmd[i] == NULL)
		exit(0);
	errno = 0;
	ms->ret = ft_atoi(cmd[i]);
	if (has_error(cmd, i, ms) == FALSE)
		exit(ms->ret);
	return (2);
}
