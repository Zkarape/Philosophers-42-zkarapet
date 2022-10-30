/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:56:09 by zkarapet          #+#    #+#             */
/*   Updated: 2022/10/29 16:57:12 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	parsing(t_data *pars, char **av, int ac)
{
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
