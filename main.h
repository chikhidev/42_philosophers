/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:01:14 by abchikhi          #+#    #+#             */
/*   Updated: 2024/04/28 18:37:18 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philo
{
    pthread_t       thread;
    int             id;
    int             times_ate;
    struct s_app    *app;
}   t_philo;

typedef struct s_app
{
    int         	philos_num;
    int         	time_to_die;
    int         	time_of_eating;
    int         	time_of_sleeping;
    int         	times_to_eat;
    int         	deads;
    t_philo         *philos;
    pthread_mutex_t	*forks;
}   t_app;

/*utils*/
int	    ft_atoi(const char *str);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *str);

/*config.c*/
int     init_data(t_app *app);

/*routine.c*/
void    *routine(void *_philo_);
int     free_everything(t_app *app);
void	join_threads(t_app *app);

#endif
