/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmarque <anmarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 01:46:45 by anmarque          #+#    #+#             */
/*   Updated: 2023/03/13 00:05:34 by anmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

t_token	*prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

t_token	*next_run(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			token = token->next;
		else if (token && token->type == CMD && token->prev->type < END)
			token = token->next;
	}
	return (token);
}

void print_tokens(t_token *token)
{
    t_token *p;

    p = token;
    while (p)
    {
        if (is_type(p, EMPTY))
		    printf("[%s][%s]\n", p->str, "EMPTY");
        else if (is_type(p, CMD))
            printf("[%s][%s]\n", p->str, "CMD");
        else if (is_type(p, ARG))
            printf("[%s][%s]\n", p->str, "ARG");
        else if (is_type(p, TRUNC))
            printf("[%s][%s]\n", p->str, "TRUNC");
        else if (is_type(p, APPEND))
            printf("[%s][%s]\n", p->str, "APPEND");
        else if (is_type(p, INPUT))
            printf("[%s][%s]\n", p->str, "INPUT");
        else if (is_type(p, PIPE))
            printf("[%s][%s]\n", p->str, "PIPE");
		else if (is_type(p, HEREDOC))
            printf("[%s][%s]\n", p->str, "HEREDOC");
        else if (is_type(p, END))
            printf("[%s][%s]\n", p->str, "END");
        p = p->next;
    }
}