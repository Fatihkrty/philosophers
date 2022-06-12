/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:39:42 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/12 14:15:03 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_status(t_philo *philo, unsigned long time, char *msg)
{
	pthread_mutex_lock(&(philo->rules->print_lock));
	pthread_mutex_lock(&(philo->rules->died_protect));
	if (!philo->rules->is_died)
		printf("%llu    %d %s\n", get_time() - time, philo->id, msg);
	pthread_mutex_unlock(&(philo->rules->died_protect));
	pthread_mutex_unlock(&(philo->rules->print_lock));
}

void	eating_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->prev_fork);
	print_status(philo, philo->start_time, TAKEN);
	pthread_mutex_lock(&(philo->fork));
	print_status(philo, philo->start_time, TAKEN);
	print_status(philo, philo->start_time, EATING);
	pthread_mutex_lock(&(philo->last_time_mutex));
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&(philo->last_time_mutex));
	smart_sleep(philo, true);
	(philo->ate_count)++;
	pthread_mutex_unlock(philo->prev_fork);
	pthread_mutex_unlock(&(philo->fork));
}

void	*create_philos(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	philo->start_time = get_time();
	if (!(philo->id % 2))
		usleep(15000);
	while (true)
	{
		eating_philo(philo);
		print_status(philo, philo->start_time, SLEEPING);
		smart_sleep(philo, false);
		print_status(philo, philo->start_time, THINKING);
		pthread_mutex_lock(&(philo->rules->died_protect));
		if (philo->rules->is_died)
		{
			pthread_mutex_unlock(&(philo->rules->died_protect));
			break ;
		}
		pthread_mutex_unlock(&(philo->rules->died_protect));
		if (philo->rules->must_eat != -1 && philo->ate_count >= philo->rules->must_eat)
			break;
	}
	return (NULL);
}