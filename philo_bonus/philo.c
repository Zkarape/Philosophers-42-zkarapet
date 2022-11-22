/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/22 21:45:37 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*is_dead_or_not_ttq(void *philo)
{
	int		i;
	long	present_time;
	t_data	*d;

	i = -1;
	d = philo;
	while (1)
	{
		sem_wait(d->sem);
		if (get_time(d->start_time) - d->last_eating_time > d->time_to_die)
		{
			printf("%ld %d is dead\n", get_time(d->start_time), d->i + 1);
			sem_post(d->p->die_sem);
			return (NULL);
		}
		sem_post(d->sem);
	}
}

void	death_thread_creation(void *philo)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL, is_dead_or_not_ttq, philo))
		error(0);
	pthread_detach(tid);
}

void	*actions(void *philo)
{
	t_data	*d;

	d = philo;
	death_thread_creation(philo);
	while (1)
	{
		sem_wait(d->p->fork_sem);
		sem_wait(d->p->fork_sem);
		printf("%ld %d has taken forks\n",
			get_time(d->start_time), d->i + 1);
		printf("%ld %d is eating\n", get_time(d->start_time), d->i + 1);
		d->last_eating_time = get_time(d->start_time);
		ft_usleep(d->time_to_eat);
		d->eating_count++;
		sem_post(d->p->fork_sem);
		sem_post(d->p->fork_sem);
		if (d->eating_count == d->must_eat)
			sem_post(d->must_eat_sem);
		printf("%ld %d is sleeping\n", get_time(d->start_time), d->i + 1);
		ft_usleep(d->time_to_sleep);
		printf("%ld %d is thinking\n", get_time(d->start_time), d->i + 1);
	}
}

void	*eat_this_much(void *data)
{
	int		i;
	t_data	*d;

	d = data;
	while (1)
	{
		i = 0;
		while (i < d[0].num_of_philos)
		{
			sem_wait(d[i].must_eat_sem);
			i++;
		}
		printf("%ld all ones have eaten >= %d times\n",
			get_time(d[0].start_time), d[0].must_eat);
		sem_post(d->p->die_sem);
	}
}

void	creation(t_main *p)
{
	pthread_t	tid;
	pid_t		pid;
	int			i;

	i = 0;
	pid = 1;
	while (i < (p->d)[0].num_of_philos)
	{
		(p->d)[i].i = i;
		pid = fork();
		if (pid == -1)
			error(1);
		else if (!pid)
			actions(&(p->d)[i]);
		i++;
	}
	if (p->d[0].must_eat > 0)
	{
		if (pthread_create(&tid, NULL, eat_this_much, p->d))
			error(0);
		pthread_detach(tid);
	}
}
