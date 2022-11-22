/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:00:37 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/22 21:40:51 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	error(int flag)
{
	if (flag == 1)
	{
		printf("Error occurred while creating or detaching thread\n");
		exit(0);
	}
	else if (flag == 2)
	{
		printf("Args are: n, time_to_die, time_to_eat, time_to_sleep\n");
		exit(0);
	}
	else if (flag == 3)
	{
		printf("Semaphore initialization error\n");
		exit(0);
	}
}
