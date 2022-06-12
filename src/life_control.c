/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:34:52 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/12 14:12:34 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	smart_sleep(t_philo *philo, bool eating)
{
	unsigned long long	start_time;

	if (eating)
	{
		while (get_time() - philo->last_eat_time <= philo->rules->time_to_eat)
			usleep(100);
	}
	else
	{
		start_time = get_time();
		while (get_time() - start_time <= philo->rules->time_to_sleep)
			usleep(100);
	}
}

void	control_philo_life_tools(t_philo *philo, t_rules *rules)
{
	static bool	printable = true;

	pthread_mutex_lock(&(philo->last_time_mutex));
	if (get_time() - philo->last_eat_time >= rules->time_to_die)
	{
		pthread_mutex_unlock(&(philo->last_time_mutex));
		pthread_mutex_lock(&(rules->died_protect));
		rules->is_died = true;
		pthread_mutex_unlock(&(rules->died_protect));
		if (printable)
		{
			printf("%llu    %d %s\n", get_time() - philo->start_time, \
			philo->id, DIED);
			printable = false;
		}
	}
	else
		pthread_mutex_unlock(&(philo->last_time_mutex));
}

void	*control_philo_life(void *void_rules)
{
	int			i;
	t_rules		*rules;

	rules = (t_rules *)void_rules;
	i = 0;
	while (!(rules->is_died))
	{
		if (i == rules->nb_philo)
			i = 0;
		control_philo_life_tools(&(rules->philosophers[i]), rules);
		i++;
		usleep(100);
	}
	return (NULL);
}
