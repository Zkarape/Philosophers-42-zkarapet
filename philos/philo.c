/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/07 22:19:00 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"
#include <fcntl.h>

void	*philo_actions(void *philo)
{
	t_data	*d;
	int		i;

	sleep(5);
	open("file", O_CREAT, 0644);
	d = philo;
	i = -1;
	while (*(d->start_from_me) != 1)
		;
	if (d->i % 2)
		usleep (500);
	while (1)
	{
		printf("smth\n");
//		pthread_mutex_lock(d->fork1);
//		pthread_mutex_lock(d->fork2);
//		getting_present_time(d, 1);
//		printf(" %d has taken forks\n", d->i);
//		getting_present_time(d, 1);
//		printf(" %d is eating\n", d->i);
//		d->eating_count++;
//		gettimeofday(&d->last_eating_time, 0);
//		usleep(d->time_to_eat * 1000);
//		pthread_mutex_unlock(d->fork1);
//		pthread_mutex_unlock(d->fork2);
//		getting_present_time(d, 1);
//		printf(" %d is sleeping\n", d->i);
//		usleep(d->time_to_sleep * 1000);
//		getting_present_time(d, 1);
//		printf(" %d is thinking\n", d->i);
	}
	return (NULL);
}

int	is_dead(t_data *data)
{
	int	last_eating_time;
	int	present_time;

	present_time = getting_present_time(data, 0) - data->start_time;
	last_eating_time = data->last_eating_time.tv_sec * 1000
		+ data->last_eating_time.tv_usec / 1000;
 	if (present_time - last_eating_time > data->time_to_die)
	{
		pthread_mutex_unlock(&data->is_dead_mutex);
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
		philos[philos->i].fork2 = &forks[philos->i + 1];
		philos[philos->i].i = philos->i;
		philos[philos->i].start_from_me = &flag;
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
