/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:46 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/08 16:23:17 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_valid_char(char c)
{
	return ((c >= '0' && c <= '9') || c == '+');
}

int	check_args(int ac, char **args)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (1);
	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!is_valid_char(args[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
