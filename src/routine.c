/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:24:21 by felperei          #+#    #+#             */
/*   Updated: 2024/07/10 09:48:05 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	philo_eat(t_philo *philo, t_program *program)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	usleep(50);
	define_forks(&first_fork, &second_fork, philo);
	pthread_mutex_lock(&first_fork->mutex_fork);
	print_fork(philo);
	if (program->n_philos == 1)
	{
		pthread_mutex_unlock(&first_fork->mutex_fork);
		return (-1);
	}
	pthread_mutex_lock(&second_fork->mutex_fork);
	print_fork(philo);
	print_eat(philo);
	pthread_mutex_lock(&philo->program->gate);
	philo->quantity_eat++;
	philo->last_eat = get_time() - philo->program->time_start;
	pthread_mutex_unlock(&philo->program->gate);
	smart_sleep(program, program->time_to_eat_ms);
	pthread_mutex_unlock(&second_fork->mutex_fork);
	pthread_mutex_unlock(&first_fork->mutex_fork);
	return (0);
}

int	monitory(t_philo *philo)
{
	while (1)
	{
		if (check_philo(philo))
			break ;
		usleep(1200);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_program	*program;

	philo = (t_philo *)arg;
	program = philo->program;
	if (philo->id_philo % 2 == 0)
		usleep(15000);
	while (check_all_alive(program) && (philo->program->must_eat == -1
			|| philo->program->must_eat > philo->quantity_eat))
	{
		if (philo_eat(philo, program))
			return (NULL);
		philo_sleep(philo, program);
		philo_thinking(philo);
	}
	return (NULL);
}
