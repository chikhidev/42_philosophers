/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:38:05 by abchikhi          #+#    #+#             */
/*   Updated: 2024/05/07 13:46:47 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int eat(t_philo *philo);
int	sleep_(t_philo *philo);
int	someone_died(t_philo *philo);
int think(t_philo *philo);

void *routine(void *_philo_)
{
    t_philo *philo;
    int     fun_res;

    fun_res = 1;
    philo = (t_philo *)_philo_;
    while (1)
    {
        fun_res = eat(philo);
        if (fun_res == -2)
            return NULL;
        else if (fun_res == -1)
        {
            UNLOCK(philo->r_fork);
            return NULL;
        }
        else if (fun_res == 0)
        {
            UNLOCK(philo->r_fork);
            UNLOCK(philo->l_fork);
            return NULL; 
        }
        
        UNLOCK(philo->r_fork);
        UNLOCK(philo->l_fork);
        
        if (!sleep_(philo))
            return NULL;
        if (!think(philo))
            return NULL;

        LOCK(&philo->app->dead_lock);
        if (philo->app->times_to_eat != -1
            && philo->times_ate >= philo->app->times_to_eat)
        {
            philo->finished = 1;
            philo->app->finished++;
            UNLOCK(&philo->app->dead_lock);
            return NULL;
        }
        UNLOCK(&philo->app->dead_lock);
    }
    return NULL;
}

int eat(t_philo *philo)
{
    if (someone_died(philo))
        return -2;

    //locking right fork
    LOCK(philo->r_fork);
    if (someone_died(philo) || philo->app->philos_num == 1)
        return -1;
    print_status(philo, TOOK_FORK);
        
    //locking left fork
    LOCK(philo->l_fork);
    if (someone_died(philo))
	    return 0;
    print_status(philo, TOOK_FORK);
    
    //modify the data
    LOCK(&philo->app->dead_lock);
    philo->last_meal = get_time();
    philo->times_ate ++;
    UNLOCK(&philo->app->dead_lock);
    print_status(philo, EATING);

    sleep_for(philo->app->time_of_eating);
    return 1;
}

int	sleep_(t_philo *philo)
{
	if (someone_died(philo))
		return 0;	
	print_status(philo, SLEEPING);
	sleep_for(philo->app->time_of_sleeping);
	return 1;
}

int	someone_died(t_philo *philo)
{
	LOCK(&philo->app->dead_lock);
	if (philo->app->deads > 0)
	{
		UNLOCK(&philo->app->dead_lock);
		return 1;
	}
	UNLOCK(&philo->app->dead_lock);
	return 0;
}

int think(t_philo *philo)
{
    if (someone_died(philo))
		return 0;
    print_status(philo, THINKING);
    return 1;
}
