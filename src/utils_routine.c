/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:24:21 by felperei          #+#    #+#             */
/*   Updated: 2024/06/25 15:03:59 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	philo_thinking(t_philo *philo)
{
	
	if (get_formatter_time(philo->time_execution) < philo->program->time_to_die_ms)
	{
		printf(BLU "%ld %d is thinking  \n" RESET,
			get_formatter_time(philo->program->time_start), philo->id_philo);
		return (0);
	}
	return (1);
}
int	philo_eat(t_philo *philo)
{
	get_forks(philo);
	pthread_mutex_lock(&philo->program->gate);
	if (get_formatter_time(philo->time_execution) < philo->program->time_to_die_ms)
	{
		printf(YEL "%ld %d is eating\n" RESET,
			get_formatter_time(philo->program->time_start), philo->id_philo);
	}
	else
	{
		release_forks(philo);
		pthread_mutex_unlock(&philo->program->gate);
		return (1);
	}
	release_forks(philo);
	usleep(philo->program->time_to_eat_ms * 1000);
	pthread_mutex_unlock(&philo->program->gate);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	// long	time_since_last_eat;
	pthread_mutex_lock(&philo->program->gate);
	// Simula o tempo de dormir
	// time_since_last_eat = get_formatter_time(philo->time_execution);
	if (philo->program->time_to_die_ms
		- philo->program->time_to_sleep_ms > philo->program->time_to_eat_ms)
	{
		printf(MAG "%ld %d is sleeping\n" RESET,
			get_formatter_time(philo->program->time_start), philo->id_philo);
	}
	else
	{
	
		pthread_mutex_unlock(&philo->program->gate);
		return (1); // Indica que o filósofo morreu
	}
	release_forks(philo);
	usleep(philo->program->time_to_sleep_ms * 1000);
	pthread_mutex_unlock(&philo->program->gate);
	return (0);
}

int	verify_died(t_philo *philo)
{
	// pthread_mutex_lock(&philo->program->gate);
	if (philo_eat(philo) == 1 || philo->program->n_philos == 1 || philo_sleep(philo) == 1
		|| philo_thinking(philo) == 1)
	{
		printf(RED "%ld %d is died  \n" RESET,
			get_formatter_time(philo->program->time_start), philo->id_philo);

		exit(1);
	}
	// release_forks(philo);
	// pthread_mutex_unlock(&philo->program->gate);
	return (1);
}
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// Usa os campos da estrutura program
	while (1)
	{
		if (!verify_died(philo))
		{
			if (philo_eat(philo))
				break ;
			// if (philo_sleep(philo))
			// 	break ;
			// if (philo_thinking(philo))
			// 	break ;
		}
		// printf("%d ms Philosopher %d is thinking\n",
		// philo->program->time_to_die_ms,
		// 	philo->id_philo);
		// printf("%d ms Philosopher %d is sleeping\n",
		// 	philo->program->time_to_sleep_ms, philo->id_philo);
		// sleep();
		// pthread_mutex_unlock(&program->forks[id_philo].mutexFork);
	}
	pthread_exit(NULL);
}
