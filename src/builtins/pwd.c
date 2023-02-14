/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:59:26 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/14 18:35:52 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

int		ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);//Liberar despues
	if (buf)
	{
		ft_putendl_fd(buf, 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
