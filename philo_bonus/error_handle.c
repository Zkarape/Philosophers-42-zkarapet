/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:00:37 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/20 15:56:00 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	error(int flag)
{
	if (flag == 1)
	{
		printf("Error occurred while forking\n");
		exit(1);
	}
	else if (flag == 3)
	{
		printf("Args are: n, time_to_die, time_to_eat, time_to_sleep\n");
		exit(1);
	}
	else if (flag == 0)
	{
		printf("Thread is not created\n");
		exit(1);
	}
	else if (flag == 5)
	{
		printf("Sem initialization error\n");
		exit(1);
	}
}
