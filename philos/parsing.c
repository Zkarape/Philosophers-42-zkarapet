/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:56:09 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/01 17:56:56 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	parsing(t_data *pars, char **av, int ac)
{
	if (!av[1] || !av[2] || !av[3] || !av[4])
		return (0);
	if (ac < 5)
		error("Args are: n, time_to_die, time_to_eat, time_to_sleep\n");
	if (ac == 6)
	{
		pars->eating_count = ft_atoi(av[5], pars);
		if ((pars->eating_count <= 0) && pars->atoi_flag == 2)
			error("Eating count for each philo must be a positive int\n");
	}
	pars->num_of_philos = ft_atoi(av[1], pars);
	pars->time_to_die = ft_atoi(av[2], pars);
	pars->time_to_eat = ft_atoi(av[3], pars);
	pars->time_to_sleep = ft_atoi(av[4], pars);
	if ((pars->num_of_philos <= 0) && pars->atoi_flag == 2)
		error("Number of philos must be a positive int\n");
	if ((pars->time_to_die) <= 0 && pars->atoi_flag == 2)
		error("Time_to_die must be a positive int\n");
	if ((pars->time_to_eat) <= 0 && pars->atoi_flag == 2)
		error("Time_to_eat must be a positive int\n");
	if ((pars->time_to_sleep) <= 0 && pars->atoi_flag == 2)
		error("Time_to_sleep must be a positive int\n");
	return (0);
}
