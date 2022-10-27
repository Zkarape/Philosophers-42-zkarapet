/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/10/27 20:58:23 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*acting_like_philo(void *philo)
{
	pthread_mutex_lock(((t_philo *)philo)->fork1);
	printf("(left) fork is taken");
	pthread_mutex_lock(((t_philo *)philo)->fork2);
	printf("(right) fork is taken");
	printf("Eating");
	gettimeofday(&((t_philo *)philo)->last_eating_time, 0);
	usleep(((t_philo *)philo)->data->time_to_eat);
	pthread_mutex_unlock(((t_philo *)philo)->fork1);
	pthread_mutex_unlock(((t_philo *)philo)->fork2);
	printf("Sleeping");
	usleep(((t_philo *)philo)->data->time_to_sleep);
	printf("Thinking");
}

void	*creation(void	*philo)
{
	int	i;

	i = -1;
	while (++i < ((t_data *)philo)->num_of_philos)
		if (pthread_create(&(((t_data *)philo)->philo_tids[i]), NULL, acting_like_philo, (t_data *)philo) != 0)
			error("Error after creating thread\n");
	i = -1;
	while (++i < ((t_data *)philo)->num_of_philos)
		if (pthread_detach(((t_data *)philo)->philo_tids[i]) != 0)
			error("Detach failed\n");
}
