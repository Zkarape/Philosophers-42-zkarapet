#ifndef PHILOS_H
# define PHILOS_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef	struct	s_data
{
	int				ac;
	char			**av;
	int				atoi_flag;
	int				num_of_philos;
	pthread_mutex_t	forks[250];
	pthread_t		philo_tids[250];
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct	timeval	last_eating_time;
}	t_data;

typedef	struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int				left;
	int				right;
	t_data			*data;
}	t_philo;

int		ft_atoi(char *s, t_data *pars);
int 	ft_strlen(char *s);
void	error(char *s);
int		parsing(t_data *pars);
void	creation(void *philo);
int		is_dead(void *data);

#endif
