/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:49 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/13 10:48:57 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int	sum;
	int	found;

	sum = 0;
	found = 1;
	while (*str == ' ' || *str == '\t' || \
			*str == '\n' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+')
		str++;
	while (*str && found)
	{
		if (*str >= '0' && *str <= '9')
			sum = sum * 10 + *str - '0';
		else
			found = 0;
		str++;
	}
	return (sum);
}
