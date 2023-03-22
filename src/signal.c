/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:09:12 by anmarque          #+#    #+#             */
/*   Updated: 2023/03/22 18:39:09 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	sig_int(int code)
{
	(void)code;
	rl_redisplay();
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_sig.pid == 0)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.pid = 0;
}
