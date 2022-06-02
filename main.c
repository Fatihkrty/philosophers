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

void print_status(t_philo *philo, unsigned long time, char *msg)
{
	pthread_mutex_lock(&(philo->rules->print_lock));
	printf("%lu    %d %s\n", get_time() - time, philo->id, msg);
	pthread_mutex_unlock(&(philo->rules->print_lock));
}

int thinking_philo(t_philo *philo)
{
	if(philo->rules->is_died > -1)
		return (1);
	print_status(philo, philo->start_time, THINKING);
	return (0);
}

int sleeping_philo(t_philo *philo)
{
	if(philo->rules->is_died > -1)
		return (1);
	unsigned long sleep_time;
	sleep_time = get_time();
	print_status(philo, philo->start_time, SLEEPING);
	while (get_time() - sleep_time <= philo->rules->time_to_sleep)
		usleep(100);
	return (0);
}

void *watch_philo_life(void *void_philo)
{
	t_philo *philo;
	philo = (t_philo *)void_philo;
	while(1)
	{
		if (philo->rules->is_died != -1 && get_time() - philo->last_eat_time >= philo->rules->time_to_die)
			break;
		usleep(100);
	}
	print_status(philo, 0, DIED);
	exit(1);
}

int eating_philo(t_philo *philo)
{
	if(philo->rules->is_died > -1)
		return (1);
	pthread_mutex_lock(philo->prev_fork);
	pthread_mutex_lock(&(philo->fork));
	philo->last_eat_time = get_time();
	print_status(philo, philo->start_time, EATING);
	while(get_time() - philo->last_eat_time <= philo->rules->time_to_eat)
		usleep(100);
	pthread_mutex_unlock(philo->prev_fork);
	pthread_mutex_unlock(&(philo->fork));
	return (0);
}

int taken_fork(t_philo *philo)
{
	if(philo->rules->is_died > -1)
		return (1);
	pthread_mutex_lock(philo->prev_fork);
	print_status(philo, philo->start_time, TAKEN);
	pthread_mutex_lock(&(philo->fork));
	print_status(philo, philo->start_time, TAKEN);
	pthread_mutex_unlock(philo->prev_fork);
	pthread_mutex_unlock(&(philo->fork));
	return (0);
}

void *create_philos(void *void_philo)
{
	t_philo *philo;
	philo = (t_philo *)void_philo;

	philo->start_time = get_time();
	if (philo->id % 2 == 0)
		usleep(100);

	while (true)
	{
		if(taken_fork(philo))
			break;
		if(eating_philo(philo))
			break;
		if(sleeping_philo(philo))
			break;
		if(thinking_philo(philo))
			break;
		usleep(100);
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
		if(pthread_create(&(rules->philosophers[i].watch), NULL, watch_philo_life, &(rules->philosophers[i])))
			return (1);
		i++;
	}

	i = 0;
	while (rules->nb_philo > i)
	{
		if(pthread_join(rules->philosophers[i].th, NULL))
			return (1);
		if(pthread_join(rules->philosophers[i].watch, NULL))
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
