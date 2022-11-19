/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/20 00:33:10 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_usleep(long time)
{
	struct timeval	start;
	struct timeval	now;
	long			present;

	gettimeofday(&now, NULL);
	present = 0;
	while (present < time)
	{
		usleep(200);
		gettimeofday(&start, NULL);
		present = (start.tv_sec * 1000 + start.tv_usec / 1000)
			- (now.tv_sec * 1000 + now.tv_usec / 1000);
	}
}

void	*actions(void *philo)
{
	t_data	*d;

	d = philo;
	while (1)
	{
		sem_wait(d->fork_sem);
		sem_wait(d->fork_sem);
		printf("%ld %d has taken a fork\n",
			get_time(d->start_time), d->i + 1);
		printf("%ld %d is eating\n", get_time(d->start_time), d->i + 1);
		d->last_eating_time = get_time(d->start_time);
		ft_usleep(d->time_to_eat);
		d->eating_count++;
		sem_post(d->fork_sem);
		sem_post(d->fork_sem);
		printf("%ld %d is sleeping\n", get_time(d->start_time), d->i + 1);
		ft_usleep(d->time_to_sleep);
		printf("%ld %d is thinking\n", get_time(d->start_time), d->i + 1);
	}
}

int	is_dead(t_data *data, int time_to_die, long present_time, int print)
{
	int	i;

	i = -1;
	if (present_time - data->last_eating_time >= time_to_die)
	{
		if (!print)
			printf("%ld %d is dead\n", present_time, data->i + 1);
		sem_post(data->die_sem);
		return (1);
	}
	return (0);
}

int	eat_this_much(t_data *d)
{
	int	i;

	i = 0;
	while (i < d[0].num_of_philos)
	{
		if (is_dead(d, d[0].time_to_die, get_time(d[0].start_time), 1))
			return (0);
		if (d[i].eating_count >= d[0].must_eat)
			i++;
	}
	if (i == d[0].num_of_philos)
		return (0);
	return (1);
}

void	creation(t_data *phs)
{
	sem_t		*sem;
	pid_t		pid;
	int			i;

	i = -1;
	pid = 1;
	while (++i < phs[0].num_of_philos && pid != 0)
	{
		phs[i].i = i;
		pid = fork();
		if (pid == -1)
		{
			error(1);
			return ;
		}
		else if (!pid)
			actions(&phs[i]);
	}
}
