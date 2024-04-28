#include "main.h"

int eat(t_philo *philo);

void *routine(void *_philo_)
{
    t_philo *philo;

    philo = (t_philo *)_philo_;
    printf("[DEBUG]: inside the thread of %d\n", philo->id);
    // if (!eat(philo))
    // {
    //     UNLOCK(philo->r_fork);
    //     UNLOCK(philo->l_fork);
    //     return NULL;
    // }
    // UNLOCK(philo->r_fork);
    // UNLOCK(philo->l_fork);
    return NULL;
}

// int eat(t_philo *philo)
// {
//     LOCK(philo->r_fork);
//     print_status(philo, TOOK_FORK);
//     LOCK(philo->l_fork);
//     print_status(philo, TOOK_FORK);
//     print_status(philo, EATING);
//     sleep_for(philo->app->time_of_eating);
//     return 1;
// }
