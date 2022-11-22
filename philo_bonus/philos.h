/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:57:27 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/22 21:43:21 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/errno.h>
# include <signal.h>

struct	s_main;

typedef struct s_data
{
	sem_t			*must_eat_sem;
	sem_t			*eat_sem;
	sem_t			*sem;
	struct s_main	*p;
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

typedef struct s_main
{
	t_data	*d;
	sem_t	*die_sem;
	sem_t	*fork_sem;
}	t_main;

void	*eat_this_much(void *data);
int		ft_atoi(char *s);
int		ft_strlen(char *s);
void	error(int flag);
void	destroying(t_data *data, pthread_mutex_t *forks);
void	freeing(t_data *data, pthread_mutex_t *forks);
void	parsing(int ac, char **av);
void	creation(t_main *data);
int		is_dead(t_data *data, int die, long present, int print);
long	get_time(long start);
void	ft_usleep(long time);

#endif
