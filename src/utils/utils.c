/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmarque <anmarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 00:48:02 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/20 15:41:25 by anmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_void(void)
{
	system("leaks -q minishell");
}

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

t_token	*ternary(t_token *cond, t_token *t1, t_token *t2)
{
	if (cond)
		return (t1);
	else
		return (t2);
}
