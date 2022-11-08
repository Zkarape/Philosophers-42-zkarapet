/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/08 21:26:35 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include <fcntl.h>

void	ft_usleep(long time)
{
	struct timeval	start;
	struct timeval	now;
	long			present;

	gettimeofday(&now, NULL);
	present = (start.tv_sec * 1000 + start.tv_usec / 1000)
			- (now.tv_sec * 1000 + now.tv_usec / 1000);
	while (present < time)
	{
		gettimeofday(&start, NULL);
		present = (start.tv_sec * 1000 + start.tv_usec / 1000)
				- (now.tv_sec * 1000 + now.tv_usec / 1000);
	}
}

void	*philo_actions(void *philo)
{
	t_data	*d;
	int		i;
	int		time;

	d = philo;
	i = -1;
	while (*(d->start_from_me) != 1)
		;
	if (d->i % 2)
		usleep (300);
	while (1)
	{
		pthread_mutex_lock(d->fork1);
		printf("%ld %d has taken a fork\n", getting_present_time(d, 1), d->i);
		pthread_mutex_lock(d->fork2);
		printf("%ld %d has taken a fork\n", getting_present_time(d, 1), d->i);
		printf("%ld %d is eating\n", getting_present_time(d, 1), d->i);
		d->last_eating_time = getting_present_time(d, 0);
		ft_usleep(d->time_to_eat);
		d->eating_count++;
		pthread_mutex_unlock(d->fork2);
		pthread_mutex_unlock(d->fork1);
		printf("%ld %d is sleeping\n", getting_present_time(d, 1), d->i);
		ft_usleep(d->time_to_sleep);
		printf("%ld %d is thinking\n", getting_present_time(d, 1), d->i);
	}
	return (NULL);
}

int	is_dead(t_data *data)
{
	long	present_time;

	present_time = getting_present_time(data, 0);
//	if (data->i == 1)
//		printf("1 == %ld 2 == %ld 3 == %ld\n", present_time, data->last_eating_time, (long)data->time_to_die);
 	if (present_time - data->last_eating_time >= (long)data->time_to_die)
	{
		//pthread_mutex_unlock(&data->is_dead_mutex);
		return (0);
	}
	return (1);
}

void	creation(t_data *philos, pthread_mutex_t *forks)
{
	int		flag;
	int		i;

	flag = 0;
	philos->i = -1;
	while (++philos->i < philos->num_of_philos)
	{
		philos[philos->i].fork1 = &forks[philos->i];
		if (philos->i + 1 == philos->num_of_philos)
			philos[philos->i].fork2 = &forks[0];
		else	
			philos[philos->i].fork2 = &forks[philos->i + 1];
		philos[philos->i].i = philos->i;
		//philos[philos->i].start_from_me = &flag;
		if (pthread_create(&philos[philos->i].tid, NULL, philo_actions, &philos[philos->i]))
		{
			error("Error after creating thread\n");
			return ;
		}
	}
	flag = 1;
	i = -1;
	while (++i < philos->num_of_philos)
		if (pthread_detach(philos[i].tid) != 0)
			error("Detach failed\n");
}
