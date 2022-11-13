/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:57:27 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/13 16:19:56 by zkarapet         ###   ########.fr       */
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
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	is_dead_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	eating_count_mutex;
	long			start_time;
	long			last_eating_time;
	int				i;
	int				*start_from_me;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eating_count;
	int				must_eat;
	int				eaten;
}	t_data;

int		ft_atoi(char *s);
int		ft_strlen(char *s);
void	error(int flag);
int		parsing(int ac, char **av);
void	creation(t_data *data, pthread_mutex_t *forks);
int		is_dead(t_data *data, int die, long present);
long	get_time_now(long start);

#endif
