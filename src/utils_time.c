/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:43:46 by felperei          #+#    #+#             */
/*   Updated: 2024/06/24 13:45:14 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	time = gettimeofday(&tv, NULL);
	time = ((long)tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

time_t get_formatter_time (time_t start_time)
{
	return (get_time() - start_time);
}