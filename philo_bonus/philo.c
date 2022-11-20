/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:39:45 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/20 18:09:26 by zkarapet         ###   ########.fr       */
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

void	*is_dead_or_not_ttq(void *philo)
{
	int		i;
	long	present_time;
	t_data	*d;

	i = -1;
	d = philo;
	while (1)
	{
	//	sem_wait(d->sem);
		present_time = get_time(d->start_time);
		if (present_time - d->last_eating_time > d->time_to_die)
		{
			printf("%ld %d is dead\n", present_time, d->i + 1);
			sem_post(d->p->die_sem);
			return (NULL);
		}
	//	sem_post(d->sem);
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
	//	sem_wait(d->eat_sem);
		i = 0;
		while (i < d[0].num_of_philos)
		{
			sem_wait(d[i].must_eat_sem);
			i++;
		}//e.g. he first one have eaten d->must_eat times, so sem_posted must_eat_sem, then program continues and i++ until the end of the cycle
		printf("%ld all ones have eaten >= %d times\n", get_time(d[0].start_time), d[0].must_eat);
		sem_post(d->p->die_sem);
	//	sem_post(d->eat_sem);
	}
}

void	creation(t_main *p)
{
	pthread_t	tid;
	pid_t		pid;
	int			i;

	i = -1;
	pid = 1;
	while (++i < (p->d)[0].num_of_philos && pid != 0)
	{
		(p->d)[i].i = i;
		pid = fork();
		if (pid == -1)
			error(1);
		else if (!pid)
			actions(&(p->d)[i]);
	}
	if (pthread_create(&tid, NULL, eat_this_much, p->d))
		error(0);
	pthread_detach(tid);
}
