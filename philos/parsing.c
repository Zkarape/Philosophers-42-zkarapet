/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:56:09 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/07 20:29:17 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	nothing_but_int(char *str)
{
	int	i;

	i = -1;
	if (!str || !*str || !ft_atoi(str))
		return (0);
	while (str[++i] && (str[i] >= '0' && str[i] <= '9'))
		;
	if (str[0] == '+')
		while (str[++i] && (str[i] >= '0' && str[i] <= '9'))
			;
	if (!str[i])
		return (1);
	return (0);
}

int	parsing(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		error("Args are: n, time_to_die, time_to_eat, time_to_sleep\n");
	if (ac == 6)
	{
		if (!nothing_but_int(av[5]))
		{
			error("Wrong args\n");
			return (0);
		}
	}
	if (!nothing_but_int(av[1]) || !nothing_but_int(av[2])
			|| !nothing_but_int(av[3]) || !nothing_but_int(av[4]))
	{
		error("Wrong args\n");
		return (0);
	}
	return (1);
}
