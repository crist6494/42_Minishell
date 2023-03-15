/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:35:38 by anmarque          #+#    #+#             */
/*   Updated: 2023/03/16 00:15:19 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>


int	ft_atoi(const char *str)
{
	int			i;
	unsigned long long	res;
	int			sign;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (10 * res) + (str[i] - 48);
		i++;
	}
	res = res * sign;
	if (sign > 0 && (int)res < 0)
		return (-1);
	else if (sign < 0 && (int)res > 0)
		return (0);
	return (res);
}

int	ft_atoi_with_check(const char *str, int *result)
{
	int			i;
	unsigned long long	res;
	int			sign;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (10 * res) + (str[i] - 48);
		i++;
		if (sign > 0 && res > LONG_MAX)
			return (0);
		//else if (sign < 0 && (res * -1) < LONG_MIN)
			//return (0);
	}
	*result = res * sign;
	return (1);
}
