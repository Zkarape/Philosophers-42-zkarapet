/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:43:48 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/13 12:38:15 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long	get_time_now(long start_time)
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

int	mutex_init(pthread_mutex_t *forks, t_data *data, int n)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->eating_count_mutex, NULL) != 0
		|| pthread_mutex_init(&data->write_mutex, NULL) != 0
		|| pthread_mutex_init(&data->is_dead_mutex, NULL))
	{
		error(5);
		return (0);
	}
	while (++i < n)
	{
		if (pthread_mutex_init(&(forks[i]), NULL) != 0)
		{
			error(5);
			return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int				i;
	int				n;
	t_data			*data;
	pthread_mutex_t	*forks;

	i = -1;
	n = ft_atoi(argv[1]);
	data = malloc(sizeof(t_data) * n);
	forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!parsing(argc, argv))
		return (0);
	mutex_init(forks, data, n);
	while (++i < n)
		filling_data(&data[i], argv);
	creation(data, forks);
	while (1)
	{
		i = -1;
		while (++i < n)
		{
			if (!is_dead(&data[i], data[i].time_to_die,
					get_time_now(data[i].start_time)))
				return (0);
		}
	}
}
