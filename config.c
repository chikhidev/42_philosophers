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

void	get_forks(t_app *app, t_philo *philo, int i)
{
	//i do have a problem in the logic of taking the forks

	// if (philo->id % 2)
	// {
	// 	philo->l_fork = &app->forks[i];
	// 	if (i + 1 < app->philos_num)
	// 		philo->r_fork = &app->forks[i + 1];
	// 	else
	// 		philo->r_fork = &app->forks[0];
	// 	printf("forks of %d are [%d, %d]\n", philo->id,
	// 		i, i + 1 < app->philos_num ? i + 1 : 0);
	// 	return ;
	// }
	// if (i + 1 < app->philos_num - 1)
	// 	philo->l_fork = &app->forks[i + 1];
	// else
	// 	philo->l_fork = &app->forks[0];
	// philo->r_fork = &app->forks[i];	
	// printf("forks of %d are [%d, %d]\n", philo->id,
	// 		i < app->philos_num ? i + 1 : 0, i);
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
		get_forks(app, &app->philos[i], i);
	}
	pthread_mutex_init(&app->print_lock, NULL);
	app->start_time = get_time();
	i = -1;
	while (++i < app->philos_num)
		pthread_create(&app->philos[i].thread, NULL, routine, &app->philos[i]);
	return 1;
}	

void	print_status(t_philo *philo, char *status)
{
	LOCK(&philo->app->print_lock);
	printf("%ld\t%d %s\n", get_time() - philo->app->start_time,
		philo->id, status);
	LOCK(&philo->app->print_lock);
}
