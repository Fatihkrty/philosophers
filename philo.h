/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:38 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/06 18:00:50 by fkaratay         ###   ########.fr       */
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

// -----------DEFINES-----------//

#define TAKEN " has taken a fork."
#define EATING " is eating."
#define SLEEPING " is sleeping."
#define THINKING " is thinking."
#define DIED " is died."


// ------------STRUCTS----------//

typedef struct s_philo
{
    int id;

    pthread_t th;

	pthread_mutex_t fork;
    pthread_mutex_t *prev_fork;
    pthread_mutex_t eating;

	unsigned long start_time;
	unsigned long last_eat_time;
	int all_ate;

    struct s_rules *rules;
} t_philo;

typedef struct s_rules
{
    int nb_philo;
    unsigned long long time_to_die;
    unsigned long long time_to_eat;
    unsigned long long time_to_sleep;
    int must_eat;

    bool is_died;

    pthread_mutex_t died_protect;

    t_philo philosophers[250];
	pthread_mutex_t print_lock;


} t_rules;

// ----------UTILS----------------//

int ft_atoi(const char *);
int check_args(int ac, char **args);
int init_app(t_rules *rules, char **args, int ac);
unsigned long get_time(void);
#endif