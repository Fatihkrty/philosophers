#include "philo.h"

int check_args(int ac, char **args)
{
    int i;
    int j;

    if (ac != 5 && ac != 6)
        return 1;
    i = 0;
    while (args[i])
    {
        j = 0;
        while (args[i][j])
        {
            if (!ft_isdigit(args[i][j]))
                return 1;
            j++;
        }
        i++;
    }
    return 0;
}

void get_time(t_philo *philo){
    struct timeval time;
    gettimeofday(&time, NULL);
    philo->sleep_time = time.tv_sec + time.tv_usec;
    return (time.tv_sec + time.tv_usec);
}

int init_app(t_rules *rules, char **args, int ac)
{
    rules->nb_philo = ft_atoi(args[0]);
    rules->time_to_die = ft_atoi(args[1]);
    rules->time_to_eat = ft_atoi(args[2]);
    rules->time_to_sleep = ft_atoi(args[3]);
    if (ac == 6)
        rules->must_eat = ft_atoi(args[4]);
    else
        rules->must_eat = 0;
    return 0;
}

void *deneme(void *data)
{
    t_philo *philo;
    t_rules *rules;

    philo = (t_philo *)data;
    rules = philo->rules;

    if (philo->id % 2 == 0)
        usleep(15000);
    printf("ID: %d\n", philo->id);
    printf("Time: %ld\n", get_time(philo));
}

void *create_thread(t_rules *rules)
{

    int i;

    i = 0;
    while (rules->nb_philo > i)
    {
        rules->philosophers[i].id = i;
        rules->philosophers[i].is_dead = 0;
        rules->philosophers[i].rules = (t_rules *)rules;
        pthread_create(&(rules->philosophers[i].th), NULL, deneme, &(rules->philosophers[i]));
        i++;
    }
    i = 0;
    while (rules->nb_philo > i)
    {
        pthread_join(rules->philosophers[i].th, NULL);
        i++;
    }
    printf("end process\n");
}

int main(int ac, char **args)
{

    t_rules rules;

    args++;
    if (check_args(ac, args) != 0)
        return 1;
    if (init_app(&rules, args, ac) != 0)
        return 1;

    create_thread(&rules);

    return 0;
}