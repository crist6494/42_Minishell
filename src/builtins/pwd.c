/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:59:26 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/12 19:53:06 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

int		ft_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
	{
		ft_putendl_fd(buf, 1);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
