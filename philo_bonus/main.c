/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:43:48 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/20 18:08:18 by zkarapet         ###   ########.fr       */
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
	data->must_eat_sem = sem_open("/must_eat_sem", O_CREAT, 0644, 0);
	data->eat_sem = sem_open("/eat_sem", O_CREAT, 0645, 1);
	data->sem = sem_open("/sem", O_CREAT, 0645, 1);
}

void	opening_sems(t_main *p, int n)
{
	p->die_sem = sem_open("/die_sem", O_CREAT, 0644, 0);
	p->fork_sem = sem_open("/fork_sem", O_CREAT, 0644, n);
}

int	main(int argc, char **argv)
{
	int		i;
	int		n;
	t_main	*p;

	i = -1;
	n = ft_atoi(argv[1]);
	p = malloc(sizeof(t_main));
	p->d = malloc(sizeof(t_data) * n);
	opening_sems(p, n);
	if (!parsing(argc, argv))
		return (0);
	while (++i < n)
		filling_data(&(p->d[i]), argv);
	creation(p);
	sem_wait(p->die_sem);
	kill(0, SIGINT);
	return (0);
}
