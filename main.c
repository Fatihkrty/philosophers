#include "philo.h"


void get_time(t_philo *philo){
    struct timeval time;
    gettimeofday(&time, NULL);
    philo->sleep_time = time.tv_sec + time.tv_usec;
    return (time.tv_sec + time.tv_usec);
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
    //printf("Time: %ld\n", get_time(philo));
}

void *create_thread(t_rules *rules)
{

    int i;

    i = 0;
    while (rules->nb_philo > i)
    {
        rules->philosophers[i].id = i;
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