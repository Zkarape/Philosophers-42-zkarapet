/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:43:48 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/13 21:26:53 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long	get_time(long start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000
			+ current_time.tv_usec / 1000) - start_time);
}

void	filling_data(t_data *data, char **av)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	data->start_time = start.tv_sec * 1000
		+ start.tv_usec / 1000;
	data->last_eating_time = 0;
	data->eating_count = 0;
}

pthread_mutex_t	*mutex_init(t_data *data, int n)
{
	int				i;
	pthread_mutex_t	*forks;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * n);
	if (pthread_mutex_init(&data[0].eating_count_mutex, NULL) != 0
		|| pthread_mutex_init(&data[0].is_dead_mutex, NULL))
	{
		error(5);
		return ((void *)0);
	}
	while (++i < n)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			error(5);
			return ((void *)0);
		}
	}
	return (forks);
}

int	main(int argc, char **argv)
{
	int				i;
	int				n;
	t_data			*data;

	i = -1;
	n = ft_atoi(argv[1]);
	data = malloc(sizeof(t_data) * n);
	if (!parsing(argc, argv))
		return (0);
	while (++i < n)
		filling_data(&data[i], argv);
	creation(data, mutex_init(data, n));
	while (1)
	{
		i = -1;
		while (++i < data[0].num_of_philos)
		{
			if (is_dead(&data[i], data[0].time_to_die,
					get_time(data[0].start_time), 0))
			{
				pthread_mutex_lock(&data[0].is_dead_mutex);
				return (0);
			}
		}
		if (argc == 6 && !eat_this_much(data))
			return (0);
	}
}
