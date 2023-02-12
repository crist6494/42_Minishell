/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:48:21 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/12 19:56:13 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	n_flag(char *str)
{
	int i;
	int n_flag;
	i = 0;
	n_flag = 0;
	
	if(str[0] != '-')
		return(n_flag);
	i++;
	while(str[i] && str[i] == 'n')
		i++;
	if(str[i] == '\0')
		n_flag = 1;
	return(n_flag);
} 

void	echo_print(char **argv,int n_flag, int fd, int i)
{
	if(!argv[i])
	{
		if(n_flag == 0)
			ft_putchar_fd('\n', fd);
		return ;
	}
	while(argv[i])
	{
		ft_putstr_fd(argv[i], fd);
		if (argv[i + 1])
			ft_putchar_fd(' ', fd);
		else if (!argv[i + 1] && !n_flag)
			ft_putchar_fd('\n', fd);
		i++;
	}
}  

int	ft_echo(char **argv)
{
	int	i;
	int	flag;
	
	flag = 0;
	i = 1;

	while (argv[i] && n_flag(argv[i]) == 1) 
	{
		flag = 1;
		i++;
	}
	echo_print(argv, flag, STDOUT, i);
	return (SUCCESS);
}