/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:34:51 by felperei          #+#    #+#             */
/*   Updated: 2024/06/25 15:04:50 by felperei         ###   ########.fr       */
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
	int	left_fork;
	int	right_fork;

	left_fork = philo->id_philo;
	right_fork = (philo->id_philo + 1) % philo->program->n_philos;
	// Filósofos com ID par pegam o garfo à esquerda primeiro
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(&philo->program->forks[left_fork]);
		printf(CYN "%ld %d has taken a fork\n" RESET,
			get_formatter_time(philo->program->time_start), philo->id_philo);
		pthread_mutex_lock(&philo->program->forks[right_fork]);
		printf(CYN "%ld %d has taken a fork\n" RESET,
			get_formatter_time(philo->program->time_start), philo->id_philo);
	}
	else
	{ // Filósofos com ID ímpar pegam o garfo à direita primeiro
		usleep(philo->program->time_to_eat_ms * 1000);
		pthread_mutex_lock(&philo->program->forks[right_fork]);
		printf(CYN "%ld %d has taken a fork \n" RESET,
			get_formatter_time(philo->program->time_start), philo->id_philo);
		if (philo->program->n_philos == 1)
		{
			printf(RED "%ld %d is died\n" RESET,
				get_formatter_time(philo->program->time_start),
				philo->id_philo);
			pthread_mutex_unlock(&philo->program->forks[left_fork]);
			exit(1);
		}
		pthread_mutex_lock(&philo->program->forks[left_fork]);
		printf(CYN "%ld %d has taken a fork\n" RESET,
			get_formatter_time(philo->program->time_start), philo->id_philo);
	}
}

void	release_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id_philo;
	right_fork = (philo->id_philo + 1) % philo->program->n_philos;
	pthread_mutex_unlock(&philo->program->forks[left_fork]);
	pthread_mutex_unlock(&philo->program->forks[right_fork]);
}
