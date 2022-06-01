/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:35 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/01 20:59:48 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->rules->print_lock));
	printf("%lu    %d %s\n", get_time(), philo->id, msg);
	pthread_mutex_unlock(&(philo->rules->print_lock));
}

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
	pthread_mutex_lock(&(philo->prev->lock_forks));
	pthread_mutex_lock(&(philo->lock_forks));
	if (philo->fork_use && philo->prev->fork_use)
	{
		// philo->fork_use = false;
		// philo->prev->fork_use = true;
		// philo->is_eat = true;
		print_status(philo, EATING);
	}
	usleep(philo->rules->time_to_eat * 10000);
	pthread_mutex_unlock(&(philo->prev->lock_forks));
	pthread_mutex_unlock(&(philo->lock_forks));
}



void taken_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->prev->lock_forks));
	pthread_mutex_lock(&(philo->lock_forks));
	
	if (!philo->fork_use && !philo->prev->fork_use)
	{
		philo->fork_use = true;
		philo->prev->fork_use = true;

	}
	else
	{
		philo->fork_use = false;
		philo->prev->fork_use = false;
	}

	pthread_mutex_unlock(&(philo->prev->lock_forks));
	pthread_mutex_unlock(&(philo->lock_forks));
	print_status(philo, TAKEN);
	eating_philo(philo);

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

	// sleeping_philo(philo);

	return NULL;
}

void *create_thread(t_rules *rules)
{
	int i;

	i = 0;
	while (rules->nb_philo > i)
	{
		pthread_create(&(rules->philosophers[i].th), NULL, create_philos, &(rules->philosophers[i]));
		i++;
		//usleep(1000);
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
