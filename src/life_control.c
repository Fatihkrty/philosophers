/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:34:52 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/09 14:35:32 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_time(unsigned long long timestamp, unsigned long long endstamp)
{
	while (get_time() - timestamp <= endstamp)
		usleep(100);
}

void	*control_philo_life(void *void_rules)
{
	int	i;
	t_rules *rules;
	static bool	printable = true;
	
	rules = (t_rules *)void_rules;
	i = 0;
	while (!(rules->is_died))
	{
		if (get_time() - rules->philosophers[i].last_eat_time >= rules->time_to_die)
		{
			pthread_mutex_lock(&(rules->died_protect));
			rules->is_died = true;
			pthread_mutex_unlock(&(rules->died_protect));
			if (printable)
			{
				printf("%lu    %d %s\n", get_time() - \
						rules->philosophers[i].start_time, rules->philosophers[i].id, DIED);
				printable = false;
			}
		}
		if (i == rules->nb_philo - 1)
			i = -1;
		i++;
		usleep(100);
	}
	
}