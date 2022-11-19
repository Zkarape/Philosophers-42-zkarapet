/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:43:48 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/20 00:32:20 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

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
	data->must_eat_sem = sem_open("/must_eat_sem", O_CREAT, 0644, 1);
}

void	opening_sems(t_data *d, int n)
{
//	d->must_eat_sem = sem_open("/must_eat_sem", O_CREAT, 0644, 1);
	d->die_sem = sem_open("/die_sem", O_CREAT, 0644, 0);
	d->fork_sem = sem_open("/fork_sem", O_CREAT, 0644, n);
}

int	main_thread_checks_dying(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data[0].num_of_philos)
	{
		if (is_dead(&data[i], data[0].time_to_die,
				get_time(data[0].start_time), 0))
		{
			sem_wait(data->die_sem);
			return (0);
		}
	}
	return (1);
}

int	conds(t_data *data,  int argc)
{
	if (!main_thread_checks_dying(data))
	{
		unlinking(data);
		return (0);
	}
	if (argc == 6 && !eat_this_much(data))
	{
		unlinking(data);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int				i;
	int				n;
	t_data			*data;

	i = -1;
	n = ft_atoi(argv[1]);
	data = malloc(sizeof(t_data) * n);
	opening_sems(data, n);
	if (!parsing(argc, argv))
		return (0);
	while (++i < n)
		filling_data(&data[i], argv);
	creation(data);
	while (1)
	{
		if (!conds(data, argc))
			return (0);
	}
	kill(0, SIGINT);
	return (0);
}
