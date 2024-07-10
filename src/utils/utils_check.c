/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:20:51 by felperei          #+#    #+#             */
/*   Updated: 2024/07/10 10:18:45 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philosophers.h"

int	check_all_alive(t_program *data)
{
	pthread_mutex_lock(&data->gate);
	if (data->al_live == 0)
	{
		pthread_mutex_unlock(&data->gate);
		return (0);
	}
	pthread_mutex_unlock(&data->gate);
	return (1);
}

int	check_died(t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->program->gate);
	current_time = get_time() - philo->program->time_start;
	if (current_time - philo->last_eat > philo->program->time_to_die_ms)
	{
		philo->program->al_live = 0;
		pthread_mutex_unlock(&philo->program->gate);
		print_died(philo);
		return (-1);
	}
	pthread_mutex_unlock(&philo->program->gate);
	return (0);
}

int	check_satisfy(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->gate);
	if (philo->quantity_eat == philo->program->must_eat)
	{
		pthread_mutex_unlock(&philo->program->gate);
		return (0);
	}
	pthread_mutex_unlock(&philo->program->gate);
	return (1);
}

int	check_all_satisfy(t_philo *philo)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < philo->program->n_philos)
	{
		if (check_satisfy(&philo[i]) == 0)
			count++;
		i++;
	}
	if (count == philo->program->n_philos)
		return (1);
	return (0);
}

int	check_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->program->n_philos)
	{
		if (check_died(&philo[i]))
			return (1);
		else if (check_all_satisfy(philo))
			break ;
		i++;
	}
	if (philo->program->must_eat != -1)
	{
		if (check_all_satisfy(philo))
			return (1);
	}
	return (0);
}
