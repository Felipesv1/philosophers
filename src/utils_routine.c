/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:24:21 by felperei          #+#    #+#             */
/*   Updated: 2024/07/08 15:42:15 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	philo_eat(t_philo *philo, t_program *program)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

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

int	check_satisfy(t_philo *philo)
{
	if (philo->quantity_eat == philo->program->n_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
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

int	check_all_satisfy(t_philo *philo)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < philo->program->n_philos)
	{
		if (check_satisfy(&philo[i]))
		{
			count++;
			if (count == philo->program->n_philos)
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->program->n_philos)
	{
		if (check_died(&philo[i]) /* || check_all_satisfy(&philo[i]) */)
			return (1);
		i++;
	}
	return (0);
}

int	monitory(t_philo *philo)
{
	// pthread_mutex_lock(&philo->program->gate);
	while (1)
	{
		if (check_philo(philo))
			break ;
		usleep(1200);
	}
	// release_forks(philo);
	// pthread_mutex_unlock(&philo->program->gate);
	return (1);
}
void	*routine(void *arg)
{
	t_philo		*philo;
	t_program	*program;

	philo = (t_philo *)arg;
	program = philo->program;
	// Usa os campos da estrutura program
	if (philo->id_philo % 2 == 0)
		usleep(1500);
	while (check_all_alive(program)
			/*
				&& philo->program->n_of_times_each_philosopher_must_eat > philo->quantity_eat */
	)
	{
		if (philo_eat(philo, program))
			return (NULL);
		philo_sleep(philo, program);
		philo_thinking(philo);
	}
	return (NULL);
}
