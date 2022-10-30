/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:57:27 by zkarapet          #+#    #+#             */
/*   Updated: 2022/10/30 19:34:08 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	int				ac;
	char			**av;
	int				atoi_flag;
	int				num_of_philos;
	pthread_mutex_t	*forks;
	pthread_t		*philo_tids;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				flag;
	int				present_time;
	struct timeval	current_time;
}	t_data;

typedef struct s_philo
{
	struct timeval	last_eating_time;
	pthread_t		tid;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int				i;
	int				*stop_please;
}	t_philo;

int		ft_atoi(char *s, t_data *pars);
int		ft_strlen(char *s);
void	error(char *s);
int		parsing(t_data *pars, char **av, int ac);
void	creation(void *philo);
int		is_dead(void *data);
int		getting_present_time(t_data *data);

#endif
