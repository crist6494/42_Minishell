/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:59:26 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/15 20:14:03 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

int		ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if(!buf)
		return(ERROR);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (SUCCESS);
}
