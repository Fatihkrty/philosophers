/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:38 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/01 20:36:37 by fkaratay         ###   ########.fr       */
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
    pthread_t watch;
	pthread_mutex_t fork;
    pthread_mutex_t *prev_fork;

	unsigned long start_time;
	unsigned long last_eat_time;

    struct s_rules *rules;

} t_philo;

typedef struct s_rules
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;

    int is_died;

    t_philo philosophers[250];
	pthread_mutex_t print_lock;


} t_rules;

// ----------UTILS----------------//

int ft_atoi(const char *);
int ft_isdigit(char c);
int check_args(int ac, char **args);
int init_app(t_rules *rules, char **args, int ac);
unsigned long get_time(void);
#endif