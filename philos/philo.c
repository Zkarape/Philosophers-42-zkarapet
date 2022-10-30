/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/10/30 18:11:18 by zkarapet         ###   ########.fr       */
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
	int		i;
	int		s = 1;

	p = philo;
	d = philo;
	i = -1;
	while (*(p->stop_please) != 1)
		;
	pthread_mutex_lock(p->fork1);
	pthread_mutex_lock(p->fork2);
	getting_present_time(1);
	printf(" %d has taken forks\n", p->i);
	getting_present_time(1);
	printf(" %d is eating\n", p->i);
	gettimeofday(&p->last_eating_time, 0);
	while (++i < d->num_of_philos);
	pthread_mutex_unlock(p->fork1);
	pthread_mutex_unlock(p->fork2);
	getting_present_time(1);
	printf(" %d is sleeping\n", p->i);
	while (++i < d->num_of_philos);
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
	t_philo	*philos;
	int		i;
	int		res;
	int		stop = 0;

	d = data;
	p = data;
	philos = malloc(sizeof(t_philo) * d->num_of_philos);
	p->i = -1;
	i = -1;
	while (++p->i < d->num_of_philos)
	{
		philos[p->i].fork1 = &d->forks[p->i];
		philos[p->i].fork2 = &d->forks[p->i + 1];
		philos[p->i].i = p->i;
		philos[p->i].stop_please = &stop;
		res = pthread_create(&philos[p->i].tid, NULL, philo_actions, &philos[p->i]);
		if (res != 0)
		{
			error("Error after creating thread\n");
			return ;
		}
	}
	stop = 1;
	i = -1;
	while (++i < d->num_of_philos)
		if (pthread_detach(philos[i].tid) != 0)
			error("Detach failed\n");
}
