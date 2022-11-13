/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 17:00:37 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/12 19:40:10 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	error(int flag)
{
	if (flag == 1)
		printf("Error occurred while creating or detaching thread\n");
	else if (flag == 3)
		printf("Args are: n, get_get_time_now_to_die, get_get_time_now_to_eat, get_get_time_now_to_sleep\n");
	else if (flag == 4)
		printf("Wrong args\n");
	else if (flag == 5)
		printf("Mutex initialization error\n");
}
