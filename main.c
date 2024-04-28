/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:01:09 by abchikhi          #+#    #+#             */
/*   Updated: 2024/04/28 20:35:20 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int init(t_app **app)
{
    *app = malloc(sizeof(t_app));
    if (!*app)
        return 0;
    (*app)->philos = NULL;
    (*app)->forks = NULL;
    (*app)->deads = 0;
    return 1;
}

int	is_overflowed_num(char *expected, int actual)
{
	char	*got;
	char	*tmp;
	int		i;

	tmp = ft_itoa(actual);
	if (!tmp)
		return (1);
	got = tmp + (expected[0] == '-' && ft_strncmp(tmp, "0", 1) != 0);
	expected += (expected[0] == '+');
	expected += (expected[0] == '-');
	i = 0;
	while (expected[i] == '0'
		&& i < (int)(ft_strlen(expected) - 1))
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

int validate_args(t_app *app, int ac, char **av)
{
    if (ac < 5 || ac > 6)
        return 0;
    app->philos_num = ft_atoi(av[1]);
    if (is_overflowed_num(av[1], app->philos_num) || app->philos_num <= 0)
        return 0;
    app->time_to_die = ft_atoi(av[2]);
    if (is_overflowed_num(av[2], app->time_to_die) || app->time_to_die <= 0)
        return 0;
    app->time_of_eating = ft_atoi(av[3]);
    if (is_overflowed_num(av[3], app->time_of_eating) || app->time_of_eating <= 0)
        return 0;
    app->time_of_sleeping = ft_atoi(av[4]);
    if (is_overflowed_num(av[4], app->time_of_sleeping) || app->time_of_sleeping <= 0)
        return 0;
    app->times_to_eat = -1;
    if (ac == 6)
    {   
        app->times_to_eat = ft_atoi(av[5]);
        return !(is_overflowed_num(av[5], app->times_to_eat) || app->times_to_eat <= 0);
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

int main(int ac, char **av)
{
    t_app *app;

    app = NULL;
    if (!init(&app) || !validate_args(app, ac, av))
        return free_everything(app);
    if (!init_data(app))
        return free_everything(app);
    join_threads(app);
    free_everything(app);
    return(0);
}
