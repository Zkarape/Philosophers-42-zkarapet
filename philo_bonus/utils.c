/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:00:49 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/19 23:38:18 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	ft_atoi(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - 48);
		i++;
	}
	return (res);
}

int	ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

long	get_time(long start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000
			+ current_time.tv_usec / 1000) - start_time);
}

//void	destroying(t_data *data, pthread_mutex_t *forks)
//{
//	int	i;
//
//	i = -1;
//	while (++i < data[0].num_of_philos)
//		pthread_mutex_destroy(&forks[i]);
//	pthread_mutex_destroy(&data[0].is_dead_mutex);
//	pthread_mutex_destroy(&data[0].eating_count_mutex);
//}

void	unlinking(t_data *data)
{
	sem_unlink("sem");
	sem_unlink("die_sem");
	sem_unlink("must_eat_sem");
}

void	freeing(t_data *data, pthread_mutex_t *forks)
{
	free(forks);
	free(data);
}
