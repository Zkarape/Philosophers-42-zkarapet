/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:43:48 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/08 17:40:33 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long	getting_present_time(t_data *data, int flag)
{
	long	present_time;

	gettimeofday(&data->current_time, NULL);
	present_time = data->current_time.tv_sec * 1000 + data->current_time.tv_usec / 1000;
	if (flag == 1)
		printf("%ld", present_time - data->start_time);
	return (present_time - data->start_time);
}

void	filling_data(t_data *data, int ac, char **av)
{
	struct timeval 	start;

	gettimeofday(&start, NULL);
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
}

int	main(int argc, char **argv)
{
	int				i;
	int				n = 0;
	t_data			*data;
	pthread_mutex_t	*forks;

	i = -1;
	if (!parsing(argc, argv))
		return (0);
	n = ft_atoi(argv[1]);
	data = malloc(sizeof(t_data) * n);
	pthread_mutex_init(&data->is_dead_mutex, NULL);
	data->eating_count = 0;
	while (++i < n)
		filling_data(&data[i], argc, argv);
	forks = malloc(sizeof(pthread_mutex_t) * n);
	while (++i < n)
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			error("Mutex initialization error\n");
	creation(data, forks);
	while (1)
	{
		i = -1;
		while (++i < n)
			if (!is_dead(&data[i]))
			{
				getting_present_time(&data[i], 1);
				printf(" %d is dead\n", i);
				pthread_mutex_lock(&data->is_dead_mutex);
				return (0);
			}
	}
}
