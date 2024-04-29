/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:38:05 by abchikhi          #+#    #+#             */
/*   Updated: 2024/04/29 17:07:50 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int eat(t_philo *philo);
int	sleep_(t_philo *philo);
int	check_dead(t_philo *philo);

void *routine(void *_philo_)
{
    t_philo *philo;

    philo = (t_philo *)_philo_;
//    printf("[DEBUG]: inside the thread of %d\n", philo->id);
    if (!eat(philo))
    {
        UNLOCK(philo->r_fork);
        UNLOCK(philo->l_fork);
        return NULL;
    }
    UNLOCK(philo->r_fork);
    UNLOCK(philo->l_fork);
    sleep_(philo);
    return NULL;
}

int eat(t_philo *philo)
{
    if (check_dead(philo))
	return 0;	
    LOCK(philo->r_fork);
    print_status(philo, TOOK_FORK);
    LOCK(philo->l_fork);
    print_status(philo, TOOK_FORK);
    print_status(philo, EATING);
    sleep_for(philo->app->time_of_eating);
    return 1;
}

int	sleep_(t_philo *philo)
{
	if (check_dead(philo))
		return 0;	
	print_status(philo, SLEEPING);
	sleep_for(philo->app->time_of_eating);
	return 1;
}

int	check_dead(t_philo *philo)
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
