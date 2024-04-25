#include "philo.h"

void    sleep_(t_philo *philo);
void    eat(t_philo *philo);
void    think(t_philo *philo);
int     get_time();
void    get_forks(t_philo *philo);

void *routine(void *philo_ptr)
{
    t_philo *philo = (t_philo *)philo_ptr;

    while (1)
    {
        if (philo->state->times_must_eat != -1 && philo->meal_count >= philo->state->times_must_eat)
            return NULL;

        philo->status = HUNGRY;

        get_forks(philo);

        eat(philo);

        UNLOCK(philo->r_fork);
        UNLOCK(philo->l_fork);

        sleep_(philo);
        think(philo);
    }
    return NULL;
}

void    get_forks(t_philo *philo)
{
    LOCK(&philo->state->forks_lock);

    philo->l_fork = &philo->state->forks[philo->id];
    philo->r_fork = &philo->state->forks[(philo->id + 1) % philo->state->number_of_philosophers];

    LOCK(philo->l_fork);
    philo->status = TOOK_FORK;
    printf("%d %d %s\n", get_time() - philo->state->start_time, philo->id, philo->status);
    LOCK(philo->r_fork);
    philo->status = TOOK_FORK;
    printf("%d %d %s\n", get_time() - philo->state->start_time, philo->id, philo->status);

    UNLOCK(&philo->state->forks_lock);
}

// void    *routine(void *philo_ptr)
// {
//     t_philo *philo;

//     philo = (t_philo *)philo_ptr;

//     while (1)
//     {
//         if (philo->state->times_must_eat != -1
//             && philo->meal_count >= philo->state->times_must_eat)
//             return (NULL);
//         LOCK(philo->r_fork);
//         LOCK(philo->l_fork);
//         eat(philo);
//         UNLOCK(philo->r_fork);
//         UNLOCK(philo->l_fork);
//         sleep_(philo->state, philo);
//         think(philo);
//     }
//     return (NULL);
// }

void	sleep_(t_philo *philo)
{
    philo->status = SLEEPING;
    printf("%d %d %s\n", get_time() - philo->state->start_time, philo->id, philo->status);
    usleep(philo->state->time_to_sleep * 1000);
}

void	eat(t_philo *philo)
{
    philo->status = EATING;
    printf("%d %d %s\n", get_time() - philo->state->start_time, philo->id, philo->status);
    philo->last_meal = get_time();
    philo->meal_count++;
}

void	think(t_philo *philo)
{
    philo->status = THINKING;
    printf("%d %d %s\n", get_time() - philo->state->start_time, philo->id, philo->status);
}
