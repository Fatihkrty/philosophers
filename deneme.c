#include "philo.h"

pthread_t th[5];
pthread_mutex_t mutex[5];

typedef struct s_timevalue
{
    time_t second;
    suseconds_t microsecond;
} timeval;


void get_time(){
    timeval timeval;

    gettimeofday(&timeval,NULL);

    printf("%ld\n", timeval.second + timeval.microsecond);
    
}

void *deneme(void *nb){
    pthread_mutex_lock(&mutex[*((int *)nb)]);
    sleep(1);
    printf("Deneme %d\n", *((int *)nb));
    get_time();
    free(nb);
    pthread_mutex_unlock(&mutex[*((int *)nb)]);
}


int main(){

    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_init(&(mutex[i]),NULL);
    }

    for (int i = 0; i < 5; i++){
        int *a = malloc(sizeof(int));
        *a = i;
        pthread_create(&th[i], NULL, deneme, a);
    }
    
    for (int i = 0; i < 5; i++){
        pthread_join(th[i], NULL);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_destroy(&(mutex[i]));
    }
    
    printf("End Process\n");

}