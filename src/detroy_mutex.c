/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detroy_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:23:33 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/09 00:22:13 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(rules->died_protect));
	pthread_mutex_destroy(&(rules->print_lock));
	pthread_mutex_destroy(&(rules->eating));
	while (rules->nb_philo > i)
	{
		pthread_mutex_destroy(&(rules->philosophers[i].fork));
		i++;
	}
}
