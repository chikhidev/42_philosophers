/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:01:14 by abchikhi          #+#    #+#             */
/*   Updated: 2024/04/28 20:20:28 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define TOOK_FORK	"has taken a fork"
#define EATING		"is eating"
#define SLEEPING	"is sleeping"
#define THINKING	"is thinking"
#define HUNGRY		"is hungry"
#define DEAD		"died"

#define LOCK	pthread_mutex_lock
#define UNLOCK	pthread_mutex_unlock

typedef struct s_philo
{
    pthread_t       thread;
    int             id;
    int             times_ate;
    struct s_app    *app;
}   t_philo;

typedef struct s_app
{
    size_t          start_time;
    int         	philos_num;
    int         	time_to_die;
    int         	time_of_eating;
    int         	time_of_sleeping;
    int         	times_to_eat;
    int         	deads;
    pthread_mutex_t print_lock;
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

/*time.h*/
size_t  get_time();
void    sleep_for(int time);

#endif
