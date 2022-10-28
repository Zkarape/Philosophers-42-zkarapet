/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/10/28 20:25:14 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*philo_actions(void *philo)
{
	t_data	*d;
	t_philo	*p;

	p = philo;
	d = philo;
	printf("(left) fork is taken\n");
	pthread_mutex_lock(&d->forks[p->right]);
	printf("(right) fork is taken\n");
	printf("Eating\n");
	gettimeofday(&d->last_eating_time, 0);
	usleep(d->time_to_eat);
	pthread_mutex_unlock(p->fork1);
	pthread_mutex_unlock(p->fork2);
	printf("Sleeping\n");
	usleep(d->time_to_sleep);
	printf("Thinking\n");
	return (NULL);
}

int	is_dead(void *data)
{
	struct timeval	current_time;
	int				present_time;
	int				last_eating_time;

	gettimeofday(&current_time, NULL);
	present_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	last_eating_time = ((t_data *)data)->last_eating_time.tv_sec * 1000 + ((t_data *)data)->last_eating_time.tv_usec * 1000;
	if (present_time - last_eating_time > ((t_data *)data)->time_to_die)
		return (0);
	return (1);
}

void	creation(void	*data)
{
	int	i;

	i = -1;
	while (++i < ((t_data *)data)->num_of_philos)
	{
		((t_philo *)data)->left = i - 1;
		((t_philo *)data)->right = i;
		if (pthread_create(&(((t_data *)data)->philo_tids[i]), NULL, philo_actions, data) != 0)
			error("Error after creating thread\n");
	}
	i = -1;
	while (++i < ((t_data *)data)->num_of_philos)
		if (pthread_detach(((t_data *)data)->philo_tids[i]) != 0)
			error("Detach failed\n");
}
