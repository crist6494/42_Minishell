/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:23:29 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/16 20:17:07 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/* static int check_sides(t_ms *ms)
{
	t_token *cmd;
	
	cmd = ms->start;
	if(!cmd)
		return (0);
	if(cmd->prev != NULL || cmd->next != NULL)
		return (1);
	return (0);
}
 */
static int	ft_check_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if(str[i] == '\0')
		return (1);
	else
		return (0);
	return (0);
}

int	ft_exit(t_ms *ms, char **cmd)
{
	
	ms->exit = 1;
	ft_putendl_fd("exit", STDERR);
	if (cmd[1] && cmd[2] && ft_check_digit(cmd[1]) == 1 && ft_check_digit(cmd[2]) == 1)
	{
		ms->exit = 0;
		ms->ret = 1;
		ft_putstr_fd("Minishell: exit: ", STDERR);
		ft_putendl_fd("too many arguments", STDERR);
	}
	else if ((cmd[2] && ft_check_digit(cmd[1]) == 0) || (ft_atoi_with_check(cmd[1], &ms->ret) == 0))
	{
		ms->ret = 255;
		ft_putstr_fd("Minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	} 
	else if(cmd[1])
		ft_atoi_with_check(cmd[1], &ms->ret);
	return (ms->ret);
}
