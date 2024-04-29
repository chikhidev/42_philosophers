/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:47:30 by abchikhi          #+#    #+#             */
/*   Updated: 2024/04/29 17:00:30 by abchikhi         ###   ########.fr       */
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
			if (get_time() - app->start_time > app->philos[i].last_meal)
			{
				print_status(&app->philos[i], DEAD);
				UNLOCK(&app->dead_lock);
				return 0;
			}
			UNLOCK(&app->dead_lock);
		}
	}
	return 1;
}
