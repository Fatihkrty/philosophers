/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:35 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/03 14:51:54 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_status(t_philo *philo, unsigned long *time, char *msg)
{
	pthread_mutex_lock(&(philo->rules->print_lock));
	if (!philo->rules->is_died)
		printf("%lu    %d %s\n", get_time() - *time, philo->id, msg);
	pthread_mutex_unlock(&(philo->rules->print_lock));
}

void thinking_philo(t_philo *philo, unsigned long *start_time)
{
	print_status(philo, start_time, THINKING);
}

void sleeping_philo(t_philo *philo, unsigned long *start_time)
{
	unsigned long sleep_time;
	sleep_time = get_time();
	print_status(philo, start_time, SLEEPING);
	while (get_time() - sleep_time <= philo->rules->time_to_sleep)
		usleep(10);
}

void control_philo_life(t_philo *philo)
{
	static bool printable = true;
	pthread_mutex_lock(&(philo->rules->protect));
	if (philo->last_eat_time && get_time() - philo->last_eat_time >= philo->rules->time_to_die)
	{
		philo->rules->is_died = true;
		if(printable)
		{
			printf("%lu    %d %s\n", get_time() - philo->start_time, philo->id, DIED);
			printable = false;
		}
	}
	pthread_mutex_unlock(&(philo->rules->protect));
}

void eating_philo(t_philo *philo, unsigned long *start_time)
{
	pthread_mutex_lock(philo->prev_fork);
	pthread_mutex_lock(&(philo->fork));
	print_status(philo, start_time, EATING);
	philo->last_eat_time = get_time();
	while(get_time() - philo->last_eat_time <= philo->rules->time_to_eat)
		usleep(10);
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(philo->prev_fork);
}

void taken_fork(t_philo *philo, unsigned long *start_time)
{

	pthread_mutex_lock(philo->prev_fork);
	pthread_mutex_lock(&(philo->fork));
	print_status(philo, start_time, TAKEN);
	print_status(philo, start_time, TAKEN);
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(philo->prev_fork);
}

void *create_philos(void *void_philo)
{
	t_philo *philo;
	unsigned long start_time;

	start_time = get_time();
	philo = (t_philo *)void_philo;

	if (philo->id % 2 == 0)
		usleep(100);
	while (true)
	{
		pthread_mutex_lock(&(philo->rules->protect));
		if(philo->rules->is_died)
		{
			pthread_mutex_unlock(&(philo->rules->protect));
			break;
		}
		pthread_mutex_unlock(&(philo->rules->protect));
		taken_fork(philo, &start_time);
		eating_philo(philo, &start_time);
		sleeping_philo(philo, &start_time);
		thinking_philo(philo, &start_time);
		control_philo_life(philo);
		usleep(10);
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
