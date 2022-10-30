/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:43:48 by zkarapet          #+#    #+#             */
/*   Updated: 2022/10/30 15:28:33 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	main(int argc, char **argv)
{
	int		i;
	t_data	*data;
	t_philo	*philo;

	i = -1;
	data = malloc(sizeof(t_data));
	philo = malloc(sizeof(t_philo));
	parsing(data, argv, argc);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	data->philo_tids = malloc(sizeof(pthread_t) * data->num_of_philos);
	if (argc == 5)
	{
		data->atoi_flag = 1;
		while (++i < data->num_of_philos)
			if (pthread_mutex_init(&data->forks[i], NULL) != 0)
				error("Mutex initialization error\n");
		i = -1;
		creation(data);
		while (++i < data->num_of_philos)
		{
			if (!is_dead(data))
			{
				getting_present_time(1);
				printf(" %d is dead\n", philo->i);
				return (0);
			}
		}
	}
}
