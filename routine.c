/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:38:05 by abchikhi          #+#    #+#             */
/*   Updated: 2024/05/09 09:06:57 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		eat(t_philo *philo);
int		sleep_(t_philo *philo);
int		someone_died(t_philo *philo);
int		eat_process(t_philo *philo);

void	*routine(void *_philo_)
{
	t_philo	*philo;

	philo = (t_philo *)_philo_;
	while (1)
	{
		if (!eat_process(philo))
			return (NULL);
		if (!sleep_(philo))
			return (NULL);
		if (someone_died(philo))
			return (NULL);
		print_status(philo, THINKING);
		LOCK(&philo->app->dead_lock);
		if (philo->app->times_to_eat != -1
			&& philo->times_ate >= philo->app->times_to_eat)
		{
			philo->finished = 1;
			philo->app->finished++;
			UNLOCK(&philo->app->dead_lock);
			return (NULL);
		}
		UNLOCK(&philo->app->dead_lock);
	}
	return (NULL);
}

int	eat_process(t_philo *philo)
{
	int	func_res;

	func_res = eat(philo);
	if (func_res == -2)
		return (0);
	else if (func_res == -1)
	{
		UNLOCK(philo->r_fork);
		return (0);
	}
	else if (func_res == 0)
	{
		UNLOCK(philo->r_fork);
		UNLOCK(philo->l_fork);
		return (0);
	}
	UNLOCK(philo->r_fork);
	UNLOCK(philo->l_fork);
	return (1);
}

int	eat(t_philo *philo)
{
	if (someone_died(philo))
		return (-2);
	LOCK(philo->r_fork);
	if (someone_died(philo))
		return (-1);
	print_status(philo, TOOK_FORK);
	if (philo->app->philos_num == 1 || someone_died(philo))
		return (-1);
	LOCK(philo->l_fork);
	if (someone_died(philo))
		return (0);
	print_status(philo, TOOK_FORK);
	if (someone_died(philo))
		return (0);
	LOCK(&philo->app->dead_lock);
	philo->last_meal = get_time();
	philo->times_ate++;
	UNLOCK(&philo->app->dead_lock);
	if (someone_died(philo))
		return (0);
	print_status(philo, EATING);
	sleep_for(philo->app->time_of_eating);
	if (someone_died(philo))
		return (0);
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
	LOCK(&philo->app->dead);
	if (philo->app->deads > 0)
	{
		UNLOCK(&philo->app->dead);
		return 1;
	}
	UNLOCK(&philo->app->dead);
	return 0;
}
