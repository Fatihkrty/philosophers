/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:59:38 by fkaratay          #+#    #+#             */
/*   Updated: 2022/06/09 14:52:36 by fkaratay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>

# define TAKEN " has taken a left fork."
# define EATING " is eating."
# define SLEEPING " is sleeping."
# define THINKING " is thinking."
# define DIED " is died."

typedef struct s_philo
{
	int				id;
	int				all_ate;
	pthread_t		th;
	pthread_mutex_t	fork;
	pthread_mutex_t	*prev_fork;
	unsigned long	start_time;
	unsigned long	last_eat_time;
	struct s_rules	*rules;
}				t_philo;

typedef struct s_rules
{
	int					nb_philo;
	int					must_eat;
	bool				is_died;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	pthread_mutex_t		died_protect;
	pthread_mutex_t		eating;
	pthread_mutex_t		print_lock;
	t_philo				philosophers[200];
}				t_rules;

unsigned long	get_time(void);
int				ft_atoi(const char *str);
int				check_args(int ac, char **args);
int				control_value(t_rules *rules);
void			print_status(t_philo *philo, unsigned long time, char *msg);
void			eating_philo(t_philo *philo);
void			*create_philos(void *void_philo);
int				init_app(t_rules *rules, char **args, int ac);
void			destroy_mutex(t_rules *rules);
void			*control_philo_life(void *vrules);
void			wait_time(unsigned long long timestamp, unsigned long long endstamp);

#endif
