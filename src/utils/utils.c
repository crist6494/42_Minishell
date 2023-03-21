/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 00:48:02 by cmorales          #+#    #+#             */
/*   Updated: 2023/03/21 13:24:55 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_void(void)
{
	system("leaks -q minishell");
}

char	*ft_strjoin_not_free(char *s1, char *s2)
{
	size_t	pos;
	char	*esp;

	if (!s1 || !s2)
		return (0);
	esp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!esp)
		return (0);
	pos = 0;
	while (*s1)
	{
		esp[pos] = *s1;
		pos++;
		s1++;
	}
	while (*s2)
	{
		esp[pos] = *s2;
		pos++;
		s2++;
	}
	esp[pos] = '\0';
	return (esp);
}

t_token	*ternary(t_token *cond, t_token *t1, t_token *t2)
{
	if (cond)
		return (t1);
	else
		return (t2);
}
