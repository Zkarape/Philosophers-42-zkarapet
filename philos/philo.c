/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/10/30 15:58:43 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	getting_present_time(int flag)
{
	struct timeval	current_time;
	int				present_time;

	gettimeofday(&current_time, NULL);
	if (flag == 1)
		printf("%ld:%d", current_time.tv_sec, current_time.tv_usec / 1000);
	present_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (present_time);
}

void	*philo_actions(void *philo)
{
	t_data	*d;
	t_philo	*p;

	p = philo;
	d = philo;
	pthread_mutex_lock(p->fork1);
	pthread_mutex_lock(p->fork2);
	getting_present_time(1);
	printf(" %d has taken forks\n", p->i);
	getting_present_time(1);
	printf(" %d is eating\n", p->i);
	gettimeofday(&p->last_eating_time, 0);
	usleep(d->time_to_eat);
	pthread_mutex_unlock(p->fork1);
	pthread_mutex_unlock(p->fork2);
	getting_present_time(1);
	printf(" %d is sleeping\n", p->i);
	usleep(d->time_to_sleep);
	getting_present_time(1);
	printf(" %d is thinking\n", p->i);
	return (NULL);
}

int	is_dead(void *data)
{
	int	present_time;
	int	last_eating_time;

	present_time = getting_present_time(0);
	last_eating_time = ((t_philo *)data)->last_eating_time.tv_sec * 1000
		+ ((t_philo *)data)->last_eating_time.tv_usec / 1000;
	if (present_time - last_eating_time > ((t_data *)data)->time_to_die)
		return (0);
	return (1);
}

void	creation(void	*data)
{
	t_philo	*p;
	t_data	*d;
	printf("num == %d\n", d->num_of_philos);
	t_philo	*philos;
	int		i;
	int		res;

	d = data;
	p = data;
	philos = malloc(sizeof(t_philo) * d->num_of_philos);
	p->i = -1;
	i = -1;
	while (++i < d->num_of_philos)
	{
		philos[i].fork1 = &d->forks[i];
		philos[i].fork2 = &d->forks[i + 1];
	}
	while (++p->i < d->num_of_philos)
	{
		res = pthread_create(&philos[p->i].tid, NULL, philo_actions, &philos[p->i]);
		if (res != 0)
			error("Error after creating thread\n");
	}
	i = -1;
	while (++i < d->num_of_philos)
		if (pthread_detach(d->philo_tids[i]) != 0)
			error("Detach failed\n");
}
