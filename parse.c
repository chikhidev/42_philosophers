#include "philo.h"

int	is_overflowed_num(char *expected, int actual)
{
	char	*got;
	char	*tmp;
	int		i;

	tmp = ft_itoa(actual);
	if (!tmp)
		return (1);
	expected += (expected[0] == '+');
	got = tmp + (expected[0] == '-');
	expected += (expected[0] == '-');
	i = 0;
	while (expected[i] == '0')
		expected++;
	if ((ft_strncmp(expected, got, ft_strlen(expected)) != 0
			&& (ft_strlen(expected) == ft_strlen(got)))
		|| ft_strlen(expected) != ft_strlen(got))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

void	validate_input(t_state *state, int ac, char **av)
{
	int		dig;

	if (ac < 5 || ac > 6)
		error(state);
	dig = ft_atoi(av[1]);
	if (is_overflowed_num(av[1], dig))
		error(state);
	dig = ft_atoi(av[2]);
	if (is_overflowed_num(av[2], dig))
		error(state);
	dig = ft_atoi(av[3]);
	if (is_overflowed_num(av[3], dig))
		error(state);
	dig = ft_atoi(av[4]);
	if (is_overflowed_num(av[4], dig))
		error(state);
	if (ac == 6)
	{
		dig = ft_atoi(av[5]);
		if (is_overflowed_num(av[5], dig))
			error(state);
	}
}

void	parse_input(t_state *state, int ac, char **av)
{
	validate_input(state, ac, av);
	state->number_of_philosophers = ft_atoi(av[1]);
	state->time_to_die = ft_atoi(av[2]);
	state->time_to_eat = ft_atoi(av[3]);
	state->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		state->times_must_eat = ft_atoi(av[5]);
	else
		state->times_must_eat = -1;
}
