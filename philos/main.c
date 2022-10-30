/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:43:48 by zkarapet          #+#    #+#             */
/*   Updated: 2022/10/30 19:30:34 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	getting_present_time(t_data *data)
{
	int		present_time;

	gettimeofday(&data->current_time, NULL);
	if (data->flag == 1)
		printf("%ld:%d", data->current_time.tv_sec, data->current_time.tv_usec / 1000);
	present_time = data->current_time.tv_sec * 1000 + data->current_time.tv_usec / 1000;
	return (present_time);
}

int	main(int argc, char **argv)
{
	int		i;
	int		stop;
	t_data	*data;
	t_philo	*philo;

	i = -1;
	stop = 0;
	data = malloc(sizeof(t_data));
	philo = malloc(sizeof(t_philo));
	parsing(data, argv, argc);
	data->flag = 0;
	data->atoi_flag = 1;
	philo->stop_please = &stop;
	data->present_time = getting_present_time(data);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	data->philo_tids = malloc(sizeof(pthread_t) * data->num_of_philos);
	if (argc == 5)
	{
		while (++i < data->num_of_philos)
			if (pthread_mutex_init(&data->forks[i], NULL) != 0)
				error("Mutex initialization error\n");
		creation(data);
	}
}
