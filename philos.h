/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:57:27 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/17 21:56:14 by zkarapet         ###   ########.fr       */
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
	int				dead;
	int				eaten;
}	t_data;

int		eat_this_much(t_data *data);
int		ft_atoi(char *s);
int		ft_strlen(char *s);
void	error(int flag);
void	destroying(t_data *data, pthread_mutex_t *forks);
void	freeing(t_data *data, pthread_mutex_t *forks);
int		parsing(int ac, char **av);
void	creation(t_data *data, pthread_mutex_t *forks);
int		is_dead(t_data *data, int die, long present, int print);
long	get_time(long start);

#endif
