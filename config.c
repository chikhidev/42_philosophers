/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:31:49 by abchikhi          #+#    #+#             */
/*   Updated: 2024/05/09 08:57:05 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	free_everything(t_app *app)
{
	free(app->philos);
	free(app->forks);
	free(app);
	return (1);
}

int	allocate(t_app *app)
{
	app->philos = malloc(sizeof(t_philo) * app->philos_num);
	if (!app->philos)
		return (0);
	app->forks = malloc(sizeof(pthread_mutex_t) * app->philos_num);
	if (!app->forks)
		return (0);
	return (1);
}

void	get_forks(t_app *app, t_philo *philo, int i)
{
	if (i % 2)
	{
		philo->r_fork = &app->forks[(i + 1) % app->philos_num];
		philo->l_fork = &app->forks[i];
		return ;
	}
	philo->r_fork = &app->forks[i];
	philo->l_fork = &app->forks[(i + 1) % app->philos_num];
}

int	init_data(t_app *app)
{
	int	i;

	if (!allocate(app))
		return (0);
	i = -1;
	app->finished = 0;
	app->start_time = get_time();
	while (++i < app->philos_num)
	{
		app->philos[i].times_ate = 0;
		app->philos[i].finished = 0;
		app->philos[i].id = i;
		app->philos[i].app = app;
		app->philos[i].last_meal = get_time();
		pthread_mutex_init(&app->forks[i], NULL);
		get_forks(app, &app->philos[i], i);
	}
	pthread_mutex_init(&app->print_lock, NULL);
	pthread_mutex_init(&app->dead_lock, NULL);
	pthread_mutex_init(&app->dead, NULL);
	i = -1;
	while (++i < app->philos_num)
		pthread_create(&app->philos[i].thread, NULL, routine, &app->philos[i]);
	return (1);
}

void	print_status(t_philo *philo, char *status)
{
	LOCK(&philo->app->dead);
	if (philo->app->deads > 0 && ft_strncmp(status, DEAD, 4) != 0)
	{
		UNLOCK(&philo->app->dead);
		return ;
	}
	LOCK(&philo->app->print_lock);
	printf("%ld\t%d %s\n", get_time() - philo->app->start_time, philo->id + 1,
			status);
	UNLOCK(&philo->app->print_lock);
	UNLOCK(&philo->app->dead);
}
