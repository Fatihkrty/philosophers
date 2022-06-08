/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:39:42 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/08 16:40:32 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_time(unsigned long long timestamp, unsigned long long endstamp)
{
	while (get_time() - timestamp <= endstamp)
		usleep(100);
}

void	control_philo_life(t_philo *philo)
{
	static bool	printable = true;

	if (philo->last_eat_time && get_time() - \
		philo->last_eat_time >= philo->rules->time_to_die)
	{
		pthread_mutex_lock(&(philo->rules->died_protect));
		philo->rules->is_died = true;
		pthread_mutex_unlock(&(philo->rules->died_protect));
		if (printable)
		{
			printf("%lu    %d %s\n", get_time() - \
					philo->start_time, philo->id, DIED);
			printable = false;
		}
	}
}
