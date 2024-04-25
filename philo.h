#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
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

typedef struct s_state
{
	int					start_time;
	int	    			time_to_die;
	int	    			time_to_eat;
	int	    			time_to_sleep;
	int	    			times_must_eat;
	int	    			number_of_philosophers;
    struct	s_philo		*philosophers;
	struct	s_monitor	*monitor;
	pthread_mutex_t		*forks;
	pthread_mutex_t		forks_lock;
	int					dead;
}	t_state;

typedef struct s_philo
{
    int	        		id;
    int         		last_meal;
    int					meal_count;
    pthread_t			thread;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	t_state				*state;
	char				*status;
}	t_philo;

/*utils.c*/
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);

/*parse.c*/
void	parse_input(t_state *state, int ac, char **av);
int		is_overflowed_num(char *expected, int actual);
void	validate_input(t_state *state, int ac, char **av);

/*utils*/
void	error(t_state *state);

/*routine.c*/
void	*routine(void *state);

/*philo.c*/
int		get_time();

#endif