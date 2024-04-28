#include "main.h"

int	free_everything(t_app *app)
{
	free(app->philos);
	free(app->forks);
	free(app);
	return 1;
}

int	allocate(t_app *app)
{
	app->philos = malloc(sizeof(t_philo) * app->philos_num);
	if (!app->philos)
		return 0;
	app->forks = malloc(sizeof(pthread_mutex_t) * app->philos_num);
	if (!app->forks)
		return 0;
	return 1;
}

int	init_data(t_app *app)
{
	int	i;
	
	if (!allocate(app))
		return 0;
	i = -1;
	while (++i < app->philos_num)
	{
		app->philos[i].times_ate = 0;
		app->philos[i].id = i;
		app->philos[i].app = app;
		pthread_mutex_init(&app->forks[i], NULL);
	}
	pthread_mutex_init(&app->print_lock, NULL);
	app->start_time = get_time();
	i = -1;
	while (++i < app->philos_num)
		pthread_create(&app->philos[i].thread, NULL, routine, &app->philos[i]);
	return 1;
}	

void	join_threads(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->philos_num)
	{
		pthread_join(app->philos[i].thread, NULL);
		i++;
	}
}

void	print_status(t_philo *philo, char *status)
{
	LOCK(&philo->app->print_lock);
	printf("%ld\t%d %s\n", get_time() - philo->app->start_time,
		philo->id, status);
	LOCK(&philo->app->print_lock);
}
