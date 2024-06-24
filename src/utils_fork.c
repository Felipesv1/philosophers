/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:34:51 by felperei          #+#    #+#             */
/*   Updated: 2024/06/24 15:45:15 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	set_forks(t_program *program)
{
	t_philo	*philo;

	philo = program->philosophers;
	if (philo->id_philo % 2 == 0)
	{
		philo->program->forks = philo->program->forks + 1;
	}
	return (0);
}

void	get_forks(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->program->n_philos)
	{
		pthread_mutex_lock(&philo->program->forks[i]);
		i++;
	}
	printf(CYN "%ld %d has taken a fork\n" RESET,
		get_formatter_time(philo->program->time_start), philo->id_philo);
}

void	release_forks(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->program->n_philos)
	{
		pthread_mutex_unlock(&philo->program->forks[i]);
		i++;
	}
	// printf("%ld ms Philosopher %d has released forks\n",
	// get_formatter_time(philo->program->time_start), philo->id_philo);
}
