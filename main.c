/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:35 by fkaratay          #+#    #+#             */
/*   Updated: 2022/05/31 21:26:28 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void print_message(pthread_mutex_t *lock, unsigned long time, int id, char *msg)
// {
// 	pthread_mutex_lock(lock);
// 	printf("%lu %d %s", time, id, msg);	
// 	pthread_mutex_unlock(lock);
// }

void sleeping_philo(t_philo *philo)
{
	if (philo->is_eat && !philo->is_sleep)
	{
		pthread_mutex_lock(&(philo->rules->print_lock));
		printf("%lu %d is sleeping.\n", get_time() - philo->start_time,philo->id);
		pthread_mutex_unlock(&(philo->rules->print_lock));
		
		pthread_mutex_lock(&(philo->lock_sleep));
		philo->is_sleep = true;
		pthread_mutex_unlock(&(philo->lock_sleep));

		usleep(philo->rules->time_to_sleep * 1000);
		
		pthread_mutex_lock(&(philo->lock_sleep));
		philo->is_sleep = false;
		pthread_mutex_unlock(&(philo->lock_sleep));

	}
}

void eating_philo(t_philo *philo)
{
	if (philo->fork_use && !philo->prev->fork_use && !philo->is_eat)
	{
		pthread_mutex_lock(&(philo->rules->print_lock));
		printf("%lu %d is eating.\n", get_time() - philo->start_time,philo->id);
		pthread_mutex_unlock(&(philo->rules->print_lock));

		usleep(philo->rules->time_to_eat * 1000);

		pthread_mutex_lock(&(philo->lock_forks));
		philo->fork_use = false;
		philo->prev->fork_use = true;
		philo->is_eat = true;
		philo->last_eat_time = get_time();
		pthread_mutex_unlock(&(philo->lock_forks));
	}
}

void taken_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->rules->print_lock));
	if (philo->fork_use && philo->prev->fork_use == false)
		printf("%lu %d has taken a fork.\n", get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(&(philo->rules->print_lock));
}

void control_philo(t_philo *philo)
{
	int i = 0;
	pthread_mutex_lock(&(philo->lock_forks));
	if (!philo->fork_use && !philo->prev->fork_use)
		philo->fork_use = false;
	// while (philo->rules->nb_philo > i)
	// {
	// 	printf("ID: %d Fork: %d\n", philo->id, philo->fork_use);
	// 	i++;
	// }
	
	pthread_mutex_unlock(&(philo->lock_forks));
}

void *create_philos(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;

	philo->start_time = get_time();
	if (philo->id % 2 == 0)
		usleep(100);

	taken_fork(philo);
	eating_philo(philo);
	sleeping_philo(philo);
	//control_philo(philo);
	
	sleep(1);

	taken_fork(philo);
	eating_philo(philo);
	sleeping_philo(philo);

	return NULL;
}

void *create_thread(t_rules *rules)
{
	int i;

	i = 0;
	while (rules->nb_philo > i)
	{
		pthread_create(&(rules->philosophers[i].th), NULL, create_philos, &(rules->philosophers[i]));
		usleep(100);
		i++;
	}

	i = 0;
	while (rules->nb_philo > i)
	{
		pthread_join(rules->philosophers[i].th, NULL);
		i++;
	}
	printf("end process\n");
	return NULL;
}

int main(int ac, char **args)
{
	t_rules rules;

	if (ac > 1)
		args++;
	if (check_args(ac, args) != 0)
		return 1;
	if (init_app(&rules, args, ac) != 0)
		return 1;
	create_mutex(&rules);
	create_thread(&rules);

	return 0;
}
