/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/13 16:39:51 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_usleep(long time)
{
	struct timeval	start;
	struct timeval	now;
	long			present;

	gettimeofday(&now, NULL);
	present = 0;
	while (present < time)
	{
		usleep(200);
		gettimeofday(&start, NULL);
		present = (start.tv_sec * 1000 + start.tv_usec / 1000)
			- (now.tv_sec * 1000 + now.tv_usec / 1000);
	}
}

void	*actions(void *philo)
{
	t_data	*d;

	d = philo;
	while (1)
	{
		pthread_mutex_lock(d->left_fork);
		pthread_mutex_lock(d->right_fork);
		printf("%ld %d has taken a left fork\n", get_time(d->start_time), d->i + 1);
		printf("%ld %d has taken a right fork\n", get_time(d->start_time), d->i + 1);
		printf("%ld %d is eating\n", get_time(d->start_time), d->i + 1);
		d->last_eating_time = get_time(d->start_time);
		ft_usleep(d->time_to_eat);
		d->eating_count++;
		pthread_mutex_unlock(d->right_fork);
		pthread_mutex_unlock(d->left_fork);
		printf("%ld %d is sleeping\n", get_time_now(d->start_time), d->i + 1);
		ft_usleep(d->time_to_sleep);
		printf("%ld %d is thinking\n", get_time_now(d->start_time), d->i + 1);
	}
}

int	is_dead(t_data *data, int time_to_die, long present_time)
{
	if (present_time - data->last_eating_time >= time_to_die)
	{
		printf("%ld %d is dead\n", present_time, data->i + 1);
		pthread_mutex_unlock(&data->is_dead_mutex);
		return (0);
	}
	return (1);
}

void	*eat_this_much(void *data)
{
	int		i;
	t_data	*d;

	d = data;
	while (1)
	{
		pthread_mutex_lock(&d[0].eating_count_mutex);
		i = 0;
		while (i < d[0].num_of_philos)
			if (d[i].eating_count >= d[0].must_eat)
				i++;
		if (i == d[0].num_of_philos)
		{
			d[0].eaten = 8;
			pthread_mutex_unlock(&d[0].is_dead_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&d[0].eating_count_mutex);
	}
}

void	creation(t_data *phs, pthread_mutex_t *forks)
{
	pthread_t	tid;
	int			flag;
	int			i;

	flag = 0;
	i = -1;
	while (++i < phs[0].num_of_philos)
	{
		phs[i].i = i;
		phs[i].left_fork = &(forks[i]);
		phs[i].right_fork = &(forks[(i + 1) % phs[i].num_of_philos]);
		if (pthread_create(&tid, NULL, actions, &phs[i]))
		{
			error(1);
			return ;
		}
		pthread_detach(tid);
	}
//	flag = 1;
	if (pthread_create(&tid, NULL, eat_this_much, phs))
	{
		error(1);
		return ;
	}
	pthread_detach(tid);
}
