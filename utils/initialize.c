/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:32 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/06 18:00:23 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int control_value(t_rules *rules)
{
	if (rules->nb_philo < 2 || rules->nb_philo > 250)
		return (1);
	if (rules->time_to_die <= 0)
		return (1);
	if (rules->time_to_eat <= 0)
		return (1);
	if (rules->time_to_sleep <= 0)
		return (1);
	if (rules->must_eat == 0 || rules->must_eat <= -2)
		return (1);
	return (0);
	
}

int init_rules(t_rules *rules, char **args, int ac)
{
	rules->nb_philo = ft_atoi(args[0]);
	rules->time_to_die = ft_atoi(args[1]);
	rules->time_to_eat = ft_atoi(args[2]);
	rules->time_to_sleep = ft_atoi(args[3]);
	rules->is_died = false;

	if (ac == 6)
		rules->must_eat = ft_atoi(args[4]);
	else
		rules->must_eat = -1;
	if(pthread_mutex_init(&(rules->print_lock), NULL))
		return (1);
	if(pthread_mutex_init(&(rules->died_protect), NULL))
		return (1);
	if (control_value(rules))
		return (1);
	return (0);

}

int init_philos(t_rules *rules)
{
	int i;

	i = 0;
	while (rules->nb_philo > i)
	{
		rules->philosophers[i].id = i + 1;
		rules->philosophers[i].rules = rules;
		rules->philosophers[i].last_eat_time = 0;
		rules->philosophers[i].all_ate = 0;
		if (i == 0)
			rules->philosophers[i].prev_fork = &(rules->philosophers[rules->nb_philo - 1].fork);
		else
			rules->philosophers[i].prev_fork = &(rules->philosophers[i - 1].fork);
		if(pthread_mutex_init(&(rules->philosophers[i].fork), NULL))
			return(1);
		if(pthread_mutex_init(&(rules->philosophers[i].eating), NULL))
			return(1);
		i++;
	}
	return (0);
}

int init_app(t_rules *rules, char **args, int ac)
{
	if(init_rules(rules, args, ac))
		return(1);
	if(init_philos(rules))
		return (1);
	return 0;
}


