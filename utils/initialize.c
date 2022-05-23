#include "../philo.h"

int init_app(t_rules *rules, char **args, int ac)
{
    rules->nb_philo = ft_atoi(args[0]);
    rules->time_to_die = ft_atoi(args[1]);
    rules->time_to_eat = ft_atoi(args[2]);
    rules->time_to_sleep = ft_atoi(args[3]);
    if (ac == 6)
        rules->must_eat = ft_atoi(args[4]);
    else
        rules->must_eat = -1;
    return 0;
}