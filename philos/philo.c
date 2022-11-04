/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/04 20:34:09 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*philo_actions(void *philo)
{
	t_data	*d;
	int		i;

	sleep(2);
	d = philo;
	i = -1;
	while (*d->start_from_me != 1)
		;
	if (d->i % 2)
		usleep (2000);
	pthread_mutex_lock(d->fork1);
	pthread_mutex_lock(d->fork2);
	getting_present_time(d);
	printf(" %d has taken forks\n", d->i);
	getting_present_time(d);
	printf(" %d is eating\n", d->i);
	gettimeofday(&d->last_eating_time, 0);
	usleep(d->time_to_eat * 1000);
//	while (++i < d->num_of_philos)
//		;
	pthread_mutex_unlock(d->fork1);
	pthread_mutex_unlock(d->fork2);
	getting_present_time(d);
	printf(" %d is sleeping\n", d->i);
	usleep(d->time_to_sleep * 1000);
//	while (++i < )
	//	;
	getting_present_time(d);
	printf(" %d is thinking\n", d->i);
	return (NULL);
}

int	is_dead(t_data *data)
{
	int	last_eating_time;

	last_eating_time = data->last_eating_time.tv_sec * 1000
		+ data->last_eating_time.tv_usec / 1000;
	if (data->present_time - last_eating_time > data->time_to_die)
		return (0);
	return (1);
}

#include <string.h>

void	creation(t_data *d)
{
	t_data	*philos;
	int		flag;
	int		i;

	flag = 0;
	d->i = -1;
	philos = malloc(sizeof(t_data) * d->num_of_philos);
	while (++d->i < d->num_of_philos)
	{
		philos[d->i].fork1 = &d->forks[d->i];
		philos[d->i].fork2 = &d->forks[d->i + 1];
		philos[d->i].i = d->i;
		philos[d->i].start_from_me = &flag;
		if (pthread_create(&philos[d->i].tid, NULL, philo_actions, &philos[d->i]))
		{
			error("Error after creating thread\n");
			return ;
		}
	}
	flag = 1;
	i = -1;
	int code = 0;
	while (++i < d->num_of_philos)
		if ((code = pthread_detach(philos[i].tid)) != 0)
			error("Detach failed\n");
}
