/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:43:48 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/06 17:47:19 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	getting_present_time(t_data *data, int flag)
{
	int		present_time;

	gettimeofday(&(data->current_time), NULL);
	if (flag == 1)
		printf("%ld:%d", data->current_time.tv_sec, data->current_time.tv_usec / 1000);
	present_time = data->current_time.tv_sec * 1000 + data->current_time.tv_usec / 1000;
	return (present_time);
}

void	filling_data(t_data *data, int ac, char **av)
{
	if (parsing(ac, av))
	{
		data->num_of_philos = ft_atoi(av[1]);
		data->time_to_die = ft_atoi(av[2]);
		data->time_to_eat = ft_atoi(av[3]);
		data->time_to_sleep = ft_atoi(av[4]);
		data->start_time = getting_present_time(data, 0);
	}
	else
		error("Wrong arg\n");
}

int	main(int argc, char **argv)
{
	int				i;
	int				n;
	t_data			*data;
	pthread_mutex_t	*forks;

	i = -1;
	if (parsing(argc, argv))
		n = ft_atoi(argv[1]);
	data = malloc(sizeof(t_data) * n);
	while (++i < n)
		filling_data(&data[i], argc, argv);
	forks = malloc(sizeof(pthread_mutex_t) * n);
	while (++i < n)
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			error("Mutex initialization error\n");
	creation(data, forks);
	i = -1;
	while (1)
		while (++i < n)
			if (!is_dead(&data[i]))
			{
				getting_present_time(&data[i], 1);
				printf(" %d is dead\n", i);
				return (0);
			}
}
