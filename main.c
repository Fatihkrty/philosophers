/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:35 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/09 15:05:05 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(t_rules *rules, pthread_t *watch)
{
	int	i;

	i = 0;
	while (rules->nb_philo > i)
	{
		if (pthread_create(&(rules->philosophers[i].th), NULL, \
			create_philos, &(rules->philosophers[i])))
			return (1);
		rules->philosophers[i].last_eat_time = get_time();
		i++;
	}
	if (pthread_create(watch, NULL, control_philo_life, rules))
		return (1);
	return (0);
}

int	join_thread(t_rules *rules, pthread_t *watch)
{
	int	i;

	i = 0;
	while (rules->nb_philo > i)
	{
		if (pthread_join(rules->philosophers[i].th, NULL))
			return (1);
		i++;
	}
	pthread_join(*watch, NULL);
	return (0);
}

int	main(int ac, char **args)
{
	t_rules	rules;
	pthread_t	watch;

	if (ac > 1)
		args++;
	if (check_args(ac, args) || init_app(&rules, args, ac))
		return (1);
	if (create_thread(&rules, &watch))
		return (1);
	if (join_thread(&rules, &watch))
		return (1);
	destroy_mutex(&rules);
	return (0);
}
