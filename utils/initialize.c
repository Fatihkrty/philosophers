/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:32 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/01 18:05:52 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void init_rules(t_rules *rules, char **args, int ac)
{
	rules->nb_philo = ft_atoi(args[0]);
	rules->time_to_die = ft_atoi(args[1]);
	rules->time_to_eat = ft_atoi(args[2]);
	rules->time_to_sleep = ft_atoi(args[3]);

	if (ac == 6)
		rules->must_eat = ft_atoi(args[4]);
	else
		rules->must_eat = -1;
	pthread_mutex_init(&(rules->protect), NULL);

}

void init_philos(t_rules *rules)
{
	int i;

	i = 0;
	while (rules->nb_philo > i)
	{
		rules->philosophers[i].id = i + 1;
		rules->philosophers[i].rules = rules;
		if (i == 0)
			rules->philosophers[i].prev_forks = &(rules->philosophers[rules->nb_philo - 1].forks);
		else
			rules->philosophers[i].prev_forks = &(rules->philosophers[i - 1].forks);
		pthread_mutex_init(&(rules->philosophers[i].forks), NULL);
		pthread_mutex_init(&(rules->philosophers[i].eat), NULL);
		pthread_mutex_init((rules->philosophers[i].prev_forks), NULL);
		i++;
	}
}

int init_app(t_rules *rules, char **args, int ac)
{
	init_rules(rules, args, ac);
	init_philos(rules);
	return 0;
}

void create_mutex(t_rules *rules)
{
	pthread_mutex_init(&(rules->print_lock), NULL);
}
