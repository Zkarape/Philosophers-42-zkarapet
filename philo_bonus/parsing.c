/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:56:09 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/22 21:43:07 by zkarapet         ###   ########.fr       */
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

void	parsing(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		error(2);
	if (ac == 6 && !nothing_but_int(av[5]))
		error(2);
	if (!nothing_but_int(av[1]) || !nothing_but_int(av[2])
		|| !nothing_but_int(av[3]) || !nothing_but_int(av[4]))
	{
		error(2);
	}
}
