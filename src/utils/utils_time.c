/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:43:46 by felperei          #+#    #+#             */
/*   Updated: 2024/07/10 09:54:42 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t	get_formatter_time(time_t start_time)
{
	return (get_time() - start_time);
}

long	time_diff(long past, long pres)
{
	return ((pres - past) * 1000);
}

void	smart_sleep(t_program *t, long time)
{
	long	past;

	past = get_time() - t->time_start;
	while (check_all_alive(t))
	{
		if (time_diff(past, get_time() - t->time_start) >= time)
			break ;
		usleep(42);
	}
}
