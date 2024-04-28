#include "main.h"

int	free_everything(t_app *app)
{
	free(app->philos);
	free(app->forks);
	free(app);
	return 1;
}

int	init_data(t_app *app)
{
	int	i;
	
	app->philos = malloc(sizeof(t_philo) * app->philos_num);
	if (!app->philos)
		return 0;
	app->forks = malloc(sizeof(pthread_mutex_t) * app->philos_num);
	if (!app->forks)
		return 0;
	i = 0;
	while (i < app->philos_num)
	{
		app->philos[i].times_ate = 0;
		app->philos[i].id = i;
		app->philos[i].app = app;
		pthread_mutex_init(&app->forks[i], NULL);
		i++;
	}
	// printf("[DEBUG]: cool!\n");
	i = 0;
	while (i < app->philos_num)
	{
		pthread_create(&app->philos[i].thread, NULL, routine, &app->philos[i]);
		i++;
	}
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
