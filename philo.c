#include "philo.h"

void	error(t_state *state);
int		get_time();
void	destroy_threads(t_state *state);
void	monitor(t_state *state);

int main(int ac, char **av)
{
	t_state	state;
	int		i;

	state.philosophers = NULL;
	state.dead = 0;
	parse_input(&state, ac, av);

	state.philosophers = malloc(sizeof(t_philo) * state.number_of_philosophers);
	if (!state.philosophers)
		error(&state);

	state.forks = malloc(sizeof(pthread_mutex_t) * state.number_of_philosophers);
	if (!state.forks)
		error(&state);

	i = 0;
	while (i < state.number_of_philosophers)
	{
		pthread_mutex_init(&state.forks[i], NULL);
		i++;
	}

	pthread_mutex_init(&state.forks_lock, NULL);

	state.start_time = get_time();
	i = 0;
	while (i < state.number_of_philosophers)
	{
		state.philosophers[i].id = i;
		state.philosophers[i].last_meal = get_time();
		state.philosophers[i].meal_count = 0;
		state.philosophers[i].slept = 0;
		state.philosophers[i].state = &state;
		state.philosophers[i].status = HUNGRY;
		state.philosophers[i].l_fork = &state.forks[i];
		state.philosophers[i].r_fork = &state.forks[(i + 1) % state.number_of_philosophers];
		pthread_create(&state.philosophers[i].thread, NULL, routine, &state.philosophers[i]);
		i++;
	}

	monitor(&state);

	i = 0;
	while (i < state.number_of_philosophers)
	{
		pthread_join(state.philosophers[i].thread, NULL);
		i++;
	}
	
	destroy_threads(&state);

	free(state.philosophers);
	free(state.forks);
	return 0;
}

void	error(t_state *state)
{
	free(state->philosophers);
	free(state->forks);
	write(2, "Error\n", 6);
	exit(1);
}

void	destroy_threads(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		pthread_join(state->philosophers[i].thread, NULL);
		i++;
	}
}

void	monitor(t_state *state)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < state->number_of_philosophers)
		{
			if (state->times_must_eat != -1 && state->philosophers[i].meal_count >= state->times_must_eat)
			{
				free(state->philosophers);
				free(state->forks);
				exit(0);
			}
			if (get_time() - state->philosophers[i].last_meal >= state->time_to_die)
			{
				printf("%d\t%d %s\n", get_time() - state->start_time, state->philosophers[i].id + 1, DEAD);
				destroy_threads(state);
				free(state->philosophers);
				free(state->forks);
				exit(1);
			}
			i++;
		}
	}
}

int	get_time()
{
    struct timeval  tv;
    int             time;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time);
}
