#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

// ----------INCLUDES----------- //

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

// ------------STRUCTS----------//

typedef struct s_philo
{
    pthread_t th;

    int id;
    int sleep_time;
    int thinking_time;
    int eating_time;
    int dead_time;

    void *rules;

} t_philo;

typedef struct s_rules
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;

    t_philo philosophers[250];

} t_rules;

// ----------UTILS----------------//

int ft_atoi(const char *);
int ft_isdigit(char c);
int check_args(int ac, char **args);
int init_app(t_rules *rules, char **args, int ac);

#endif