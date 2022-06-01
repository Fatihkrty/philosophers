/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:38 by fkaratay          #+#    #+#             */
/*   Updated: 2022/05/31 20:40:44 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// ----------INCLUDES----------- //

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdbool.h>

// ------------STRUCTS----------//

typedef struct s_philo
{
    int id;

    pthread_t th;
	pthread_mutex_t lock_forks;
	pthread_mutex_t lock_sleep;

	bool fork_use;
	bool is_eat;
	bool is_sleep;

	unsigned long start_time;
	unsigned long last_eat_time;

	struct s_philo *prev;
    struct s_rules *rules;

} t_philo;

typedef struct s_rules
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
	bool is_dead;

    t_philo philosophers[250];
	pthread_mutex_t print_lock;

} t_rules;

// ----------UTILS----------------//

int ft_atoi(const char *);
int ft_isdigit(char c);
int check_args(int ac, char **args);
int init_app(t_rules *rules, char **args, int ac);
void create_mutex(t_rules *rules);
unsigned long get_time(void);
#endif