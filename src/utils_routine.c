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

static void define_forks(t_fork **first_fork,
						 t_fork **second_fork, t_philo *philo)
{
	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}
void philo_thinking(t_philo *philo)
{
	printf(BLU "%ld %d is thinking  \n" RESET,
		   get_formatter_time(philo->program->time_start), philo->id_philo);
}
void philo_eat(t_philo *philo)
{
	t_fork *first_fork;
	t_fork *second_fork;
	define_forks(&first_fork, &second_fork, philo);
	pthread_mutex_lock(&first_fork->mutex_fork);
	printf(CYN "%ld %d has taken a fork\n" RESET,
		   get_formatter_time(philo->program->time_start), philo->id_philo);
	pthread_mutex_lock(&second_fork->mutex_fork);
	printf(CYN "%ld %d has taken a fork\n" RESET,
		   get_formatter_time(philo->program->time_start), philo->id_philo);
	printf(YEL "%ld %d is eating\n" RESET,
		   get_formatter_time(philo->time_execution), philo->id_philo);
	pthread_mutex_lock(&philo->program->gate);
	philo->quantity_eat++;
	philo->last_eat = get_time() - philo->program->time_start;
	pthread_mutex_unlock(&philo->program->gate);
	usleep(philo->program->time_to_eat_ms);
	pthread_mutex_unlock(&first_fork->mutex_fork);
	pthread_mutex_unlock(&second_fork->mutex_fork);

}

void philo_sleep(t_philo *philo)
{

	pthread_mutex_lock(&philo->program->gate);
	printf(MAG "%ld %d is sleeping\n" RESET,
		   get_formatter_time(philo->program->time_start), philo->id_philo);
	// release_forks(philo);
	pthread_mutex_unlock(&philo->program->gate);
}
int check_satisfy(t_philo *philo)
{
	if (philo->quantity_eat == philo->program->n_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}
int check_died(t_philo *philo)
{
	long current_time;

	current_time = get_time() - philo->program->time_start;
	pthread_mutex_lock(&philo->program->gate);

	if (current_time - philo->last_eat > philo->program->time_to_die_ms)
	{
		philo->program->al_live = 0;
		printf(RED "%ld %d is died\n" RESET, get_formatter_time(philo->program->time_start),
			   philo->id_philo);
		pthread_mutex_unlock(&philo->program->gate);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->gate);

	return (0);
}

int check_all_satisfy(t_philo *philo)
{
	int i;
	int count;

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

int check_philo(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->program->n_philos)
	{
		// philo[i].last_eat = get_time();
		if (check_died(&philo[i]) /* || check_all_satisfy(&philo[i]) */)
			return (1);
		i++;
	}
	return (0);
}

int monitory(t_philo *philo)
{
	// pthread_mutex_lock(&philo->program->gate);
	while (1)
	{
		if (check_philo(philo))
			break;
		usleep(60);
	}
	// release_forks(philo);
	// pthread_mutex_unlock(&philo->program->gate);
	return (1);
}
void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// Usa os campos da estrutura program
	if (philo->id_philo % 2 == 0)
		usleep(500);
	while (philo->program->al_live == 1
		   /*
			   && philo->program->n_of_times_each_philosopher_must_eat > philo->quantity_eat */
	)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_thinking(philo);
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
