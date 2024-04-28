#include "main.h"

void *routine(void *_philo_)
{
    t_philo *philo;

    philo = (t_philo *)_philo_;
    printf("[DEBUG]: inside the thread of %d\n", philo->id);
    return NULL;
}

// int eat(t_philo *philo)
// {

// }