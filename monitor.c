/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:47:30 by abchikhi          #+#    #+#             */
/*   Updated: 2024/05/09 08:53:45 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	monitor(t_app *app)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < app->philos_num)
		{
			LOCK(&app->dead_lock);
			if (app->times_to_eat != -1
            	&& app->finished == app->philos_num)
			{
				UNLOCK(&app->dead_lock);
				return 1;
			}
			if (get_time() - app->philos[i].last_meal > (size_t)app->time_to_die
				&& !app->philos[i].finished)
			{
				LOCK(&app->dead);
				app->deads += 1;
				UNLOCK(&app->dead);
				print_status(&app->philos[i], DEAD);
				UNLOCK(&app->dead_lock);
				return 0;
			}
			UNLOCK(&app->dead_lock);
		}
	}
	return 1;
}
