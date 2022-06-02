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

void thinking_philo(t_philo *philo)
{
	print_status(philo, philo->start_time, THINKING);
}

void sleeping_philo(t_philo *philo)
{
	unsigned long sleep_time;
	sleep_time = get_time();
	print_status(philo, philo->start_time, SLEEPING);
	while (get_time() - sleep_time <= philo->rules->time_to_sleep)
		usleep(100);	
}

void eating_philo(t_philo *philo)
{
	philo->last_eat_time = get_time();
	print_status(philo, philo->start_time, EATING);
	while(get_time() - philo->last_eat_time <= philo->rules->time_to_eat)
		usleep(100);
	pthread_mutex_unlock(philo->prev_forks);
	pthread_mutex_unlock(&(philo->forks));
}



void taken_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->prev_forks);
	print_status(philo, philo->start_time, TAKEN);
	pthread_mutex_lock(&(philo->forks));
	print_status(philo, philo->start_time, TAKEN);
}

void *create_philos(void *void_philo)
{
	t_philo *philo;
	philo = (t_philo *)void_philo;

	philo->start_time = get_time();
	if (philo->id % 2 == 0)
		usleep(1000);

	while (true)
	{
		taken_fork(philo);
		eating_philo(philo);
		sleeping_philo(philo);
		thinking_philo(philo);
		usleep(100);
	}


	//taken_fork(philo);
	//eating_philo(philo);
	//sleeping_philo(philo);

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
