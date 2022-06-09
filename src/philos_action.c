/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:39:42 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/09 13:32:16 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_time(unsigned long long timestamp, unsigned long long endstamp)
{
	while (get_time() - timestamp <= endstamp)
		usleep(100);
}

void	*control_philo_life(void *vrules)
{
	printf("geldi\n");
	int	i;
	static bool	printable = true;
	t_rules *rules;
	rules = (t_rules *)vrules;
	i = 0;
	while (!(rules->is_died))
	{
		//printf("last: %d\n", get_time() - rules->philosophers[i].last_eat_time >= rules->time_to_die);
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
