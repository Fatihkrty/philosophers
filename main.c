#include "philo.h"


unsigned long get_time(t_philo *philo){
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
        usleep(1500);
    pthread_mutex_lock(&(rules->lock));
    printf("ID: %d\n", philo->id);
    printf("Time: %ld\n", get_time(philo));
    pthread_mutex_unlock(&(rules->lock));

}

void *create_thread(t_rules *rules)
{

    int i;

    i = 0;
    while (rules->nb_philo > i)
    {
        rules->philosophers[i].id = i;
        rules->philosophers[i].rules = (t_rules *)rules;
        //pthread_mutex_init(&(rules->philosophers[i].left_fork), NULL);
        pthread_create(&(rules->philosophers[i].th), NULL, deneme, &(rules->philosophers[i]));
        i++;
    }
    i = 0;
    while (rules->nb_philo > i)
    {
        pthread_join(rules->philosophers[i].th, NULL);
        //pthread_mutex_destroy(&(rules->philosophers[i].left_fork));
        i++;
    }
    printf("end process\n");
}

int main(int ac, char **args)
{
    t_rules rules;
    pthread_mutex_init(&(rules.lock), NULL);

    args++;
    if (check_args(ac, args) != 0)
        return 1;
    if (init_app(&rules, args, ac) != 0)
        return 1;

    create_thread(&rules);
    pthread_mutex_destroy(&(rules.lock));

    return 0;
}