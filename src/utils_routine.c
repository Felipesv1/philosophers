/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:24:21 by felperei          #+#    #+#             */
/*   Updated: 2024/06/26 15:34:14 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philo_thinking(t_philo *philo)
{
	printf(BLU "%ld %d is thinking  \n" RESET,
		get_formatter_time(philo->program->time_start), philo->id_philo);
}
void	philo_eat(t_philo *philo)
{
	get_forks(philo);
	pthread_mutex_lock(&philo->program->gate);
	// Atualize last_eat com o tempo atual
	// pthread_mutex_lock(&philo->program->mutex_block);
	printf(YEL "%ld %d is eating\n" RESET,
		get_formatter_time(philo->time_execution), philo->id_philo);
	philo->quantity_eat++;
	usleep(philo->program->time_to_eat_ms * 1000);
	release_forks(philo);
	// pthread_mutex_unlock(&philo->program->mutex_block);
	pthread_mutex_unlock(&philo->program->gate);
}

void	philo_sleep(t_philo *philo)
{
	// long	time_since_last_eat;
	pthread_mutex_lock(&philo->program->gate);
	// Simula o tempo de dormir
	// time_since_last_eat = get_formatter_time(philo->time_execution);
	printf(MAG "%ld %d is sleeping\n" RESET,
		get_formatter_time(philo->program->time_start), philo->id_philo);
	/* usleep(philo->program->time_to_sleep_ms * 1000); */
	// release_forks(philo);
	pthread_mutex_unlock(&philo->program->gate);
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
	current_time = get_time();
	// printf("%ld current\n", current_time);
	// printf("%ld execution\n", philo->time_execution);
	// printf("%ld last_eat\n", philo->last_eat);
	// printf("%ld diferenca\n", current_time - philo->last_eat);
	// printf("%ld time_to_die\n", philo->program->time_to_die_ms * 1000);
	if (current_time - philo->last_eat > philo->program->time_to_die_ms)
	{
		philo->program->al_live = 0;
		printf(RED "%ld %d is died\n" RESET, get_formatter_time(current_time),
			philo->id_philo);
		pthread_mutex_unlock(&philo->program->gate);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->gate);
	printf("aaaaa\n");

	
	return (0);
}

int	check_all_satisfy(t_philo *philo)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (&philo[i])
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
	while (&philo[i])
	{
		philo[i].last_eat = get_time();
		if (check_died(&philo[i]) /* || check_all_satisfy(&philo[i]) */)
			return (1);
		i++;
	}
	printf("xxx\n");

	return (0);
}

int	monitory(t_philo *philo)
{
	// pthread_mutex_lock(&philo->program->gate);
	while (1)
	{
		if (check_philo(philo))
			break ;
		usleep(60);
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
	if (philo->id_philo % 2 == 0)
		usleep(500);
	while (philo->program->al_live == 1
			/*
				&& philo->program->n_of_times_each_philosopher_must_eat > philo->quantity_eat */)
	{
		philo_eat(philo);
		philo_sleep(philo);
		// if (philo_thinking(philo))
		// 	break ;
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
