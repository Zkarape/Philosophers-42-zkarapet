/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/10/28 17:21:37 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*philo_actions(void *philo)
{
	pthread_mutex_lock(((t_data *)philo)->forks[left]);
	printf("(left) fork is taken\n");
	pthread_mutex_lock(((t_data *)philo)->forks[right]);
	printf("(right) fork is taken\n");
	printf("Eating\n");
	gettimeofday(&((t_data *)philo)->last_eating_time, 0);
	usleep(((t_data *)philo)->time_to_eat);
	pthread_mutex_unlock(((t_philo *)philo)->fork1);
	pthread_mutex_unlock(((t_philo *)philo)->fork2);
	printf("Sleeping\n");
	usleep(((t_data *)philo)->time_to_sleep);
	printf("Thinking\n");
	return (NULL);
}

void	creation(void	*data)
{
	int	i;

	i = 0;
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
