/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 00:48:02 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/13 17:37:05 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_void()
{
	system("leaks -q minishell"); //Mirar procesos cuando sale
}

/* int	usage_message(t_ms *ms, int state)
{
	ms->iterative = state;
	ft_putendl_fd("Usage: ./minishell", 2);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", 2);
	return (state);
} */

int	ft_tokensize(t_token *token)
{
	int		size;
	t_token	*p;

	p = token;
	size = 0;
	while (p != NULL)
	{
		if (is_type(p, CMD))
			size++;
		p = p->next;
	}
	return (size);
}