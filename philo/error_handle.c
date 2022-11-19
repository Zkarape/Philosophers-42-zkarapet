/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:00:37 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/13 16:49:39 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	error(int flag)
{
	if (flag == 1)
	{
		printf("Error occurred while creating or detaching thread\n");
	}
	else if (flag == 3)
	{
		printf("Args are: n, time_to_die, time_to_eat, time_to_sleep\n");
	}
	else if (flag == 4)
		printf("Wrong args\n");
	else if (flag == 5)
		printf("Mutex initialization error\n");
}
