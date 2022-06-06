/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:35 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/06 17:55:02 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void control_philo_life(t_philo *philo)
{
	static bool printable = true;
	if (philo->last_eat_time && get_time() - philo->last_eat_time >= philo->rules->time_to_die)
	{
		pthread_mutex_lock(&(philo->rules->died_protect));
		philo->rules->is_died = true;
		pthread_mutex_unlock(&(philo->rules->died_protect));
		if(printable)
		{
			printf("%lu    %d %s\n", get_time() - philo->start_time, philo->id, DIED);
			printable = false;
		}
	}
}

void print_status(t_philo *philo, unsigned long time, char *msg)
{
	pthread_mutex_lock(&(philo->rules->print_lock));
	pthread_mutex_lock(&(philo->rules->died_protect));
	if (!philo->rules->is_died)
		printf("%lu    %d %s\n", get_time() - time, philo->id, msg);
	pthread_mutex_unlock(&(philo->rules->died_protect));
	pthread_mutex_unlock(&(philo->rules->print_lock));
}

void wait_time(unsigned long long timestamp, unsigned long long endstamp)
{
	while(get_time() - timestamp <= endstamp)
		usleep(100);
}

void eating_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->prev_fork);
	print_status(philo, philo->start_time, TAKEN);
	pthread_mutex_lock(&(philo->fork));
	print_status(philo, philo->start_time, TAKEN);
	pthread_mutex_lock(&(philo->eating));
	print_status(philo, philo->start_time, EATING);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&(philo->eating));
	wait_time(philo->last_eat_time, philo->rules->time_to_eat);
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(philo->prev_fork);
}

void *create_philos(void *void_philo)
{
	t_philo *philo;

	philo = (t_philo *)void_philo;
	if (!(philo->id % 2))
		usleep(1000);
	philo->start_time = get_time();
	while (true)
	{
		eating_philo(philo);
		print_status(philo, philo->start_time, SLEEPING);
		wait_time(get_time(), philo->rules->time_to_sleep);
		print_status(philo, philo->start_time, THINKING);
		control_philo_life(philo);
		pthread_mutex_lock(&(philo->rules->died_protect));
		if(philo->rules->is_died)
		{
			pthread_mutex_unlock(&(philo->rules->died_protect));
			break;
		}
		pthread_mutex_unlock(&(philo->rules->died_protect));
	}
	return NULL;
}

int create_thread(t_rules *rules)
{
	int i;

	i = 0;
	while (rules->nb_philo > i)
	{
		if(pthread_create(&(rules->philosophers[i].th), NULL, create_philos, &(rules->philosophers[i])))
			return (1);
		i++;
	}

	i = 0;
	while (rules->nb_philo > i)
	{
		if(pthread_join(rules->philosophers[i].th, NULL))
			return (1);
		i++;
	}
	return (0);
}

int main(int ac, char **args)
{
	t_rules rules;

	if (ac > 1)
		args++;
	if (check_args(ac, args) || init_app(&rules, args, ac))
		return (1);
	if(create_thread(&rules))
		return (1);
	return (0);
}
