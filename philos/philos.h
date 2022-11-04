/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:57:27 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/04 20:25:33 by zkarapet         ###   ########.fr       */
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
	struct timeval	last_eating_time;
	pthread_t		tid;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int				i;
	int				*start_from_me;
	int				ac;
	char			**av;
	int				atoi_flag;
	int				num_of_philos;
	pthread_mutex_t	*forks;
	pthread_t		*philo_tids;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eating_count;
	int				flag;
	int				present_time;
	int				start_from;
	struct timeval	current_time;
}	t_data;

int		ft_atoi(char *s, t_data *pars);
int		ft_strlen(char *s);
void	error(char *s);
int		parsing(t_data *pars, char **av, int ac);
void	creation(t_data *data);
int		is_dead(t_data *data);
int		getting_present_time(t_data *data);

#endif
