#include "../philo.h"

void destroy_mutex(t_rules *rules)
{
    int i;

    i = 0;
    pthread_mutex_destroy(&(rules->died_protect));
    pthread_mutex_destroy(&(rules->print_lock));
    while (rules->nb_philo > i)
    {
        pthread_mutex_destroy(&(rules->philosophers[i].fork));
        pthread_mutex_destroy(&(rules->philosophers[i].eating));
        i++;
    }
    
}