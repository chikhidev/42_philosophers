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
        if (philo->state->number_of_philosophers == 1)
        {
            get_forks(philo);
            return NULL;
        }

        philo->slept = 0;
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
    philo->l_fork = &philo->state->forks[philo->id];
    LOCK(philo->l_fork);
    philo->status = TOOK_FORK;
    printf("%d\t%d %s\n", get_time() - philo->state->start_time, philo->id + 1, philo->status);
    UNLOCK(philo->l_fork);

    if (philo->id == 0 && philo->state->number_of_philosophers > 2)
        philo->r_fork = &philo->state->forks[philo->state->number_of_philosophers - 1];
    else if (philo->state->number_of_philosophers > 2)
        philo->r_fork = &philo->state->forks[philo->id - 1];
    else
        return ;
    
    LOCK(philo->r_fork);
    philo->status = TOOK_FORK;
    printf("%d\t%d %s\n", get_time() - philo->state->start_time, philo->id + 1, philo->status);
    UNLOCK(philo->r_fork);
}

void	sleep_(t_philo *philo)
{
    if (philo->slept)
        return ;
    philo->status = SLEEPING;
    printf("%d\t%d %s\n", get_time() - philo->state->start_time, philo->id + 1, philo->status);
    printf("sleeping %d\n", philo->state->time_to_sleep * 1000);
    usleep(philo->state->time_to_sleep * 1000);
    philo->slept = 1;
}

void	eat(t_philo *philo)
{
    philo->status = EATING;
    philo->last_meal = get_time();
    printf("%d\t%d %s\n", philo->last_meal - philo->state->start_time, philo->id + 1, philo->status);
    usleep(philo->state->time_to_eat * 1000);
    philo->meal_count++;
}

void	think(t_philo *philo)
{
    philo->status = THINKING;
    printf("%d\t%d %s\n", get_time() - philo->state->start_time, philo->id + 1, philo->status);
}
