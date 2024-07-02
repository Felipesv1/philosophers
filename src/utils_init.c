/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:36:09 by felperei          #+#    #+#             */
/*   Updated: 2024/06/26 15:28:18 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	init_program(char **av)
{
	t_program	*program;

	program = (t_program *)malloc(sizeof(t_program));
	program->n_philos = ft_atoi(av[1]);
	program->philosophers = (t_philo *)malloc(program->n_philos
			* sizeof(t_philo));
	program->forks = (t_fork *)malloc(program->n_philos
			* sizeof(t_fork));
	program->time_start = get_time();
	program->al_live = 1;
	program->philosophers->quantity_eat = 1;
	program->time_to_die_ms = ft_atoi(av[2]);
	program->time_to_eat_ms = ft_atoi(av[3]) * 1000;
	program->time_to_sleep_ms = ft_atoi(av[4]) * 1000;
	if (av[5])
		program->n_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	init_philos(program);
	init_threads_philo(program);
	// free_program(program);
}

int	init_threads_philo(t_program *program)
{
	int	i;

	// int				*id_philo;
	i = 0;
	pthread_mutex_init(&program->gate, NULL);
	pthread_mutex_init(&program->mutex_block, NULL);
	while (i < program->n_philos)
	{
		pthread_mutex_init(&program->forks[i].mutex_fork, NULL);
		program->forks[i].fork_id = i + 1;
		if (pthread_create(&program->philosophers[i].philo, NULL, &routine,
				&program->philosophers[i]) != 0)
		{
			perror("Failed to create thread");
			free(program->philosophers);
			return (1);
		}
		i++;
	}
	monitory(program->philosophers);
	i = 0;
	while (i < program->n_philos)
	{
		if (pthread_join(program->philosophers[i].philo, NULL) != 0)
		{
			perror("Falha ao esperar pela thread");
			free(program->philosophers);
			return (2);
		}
		i++;
	}
	i = 0;
	while (i < program->n_philos)
	{
		pthread_mutex_destroy(&program->forks[i].mutex_fork);
		i++;
	}
	pthread_mutex_destroy(&program->gate);
	pthread_mutex_destroy(&program->mutex_block);
	return (0);
}

int	init_philos(t_program *program)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = program->philosophers;
	while (i < program->n_philos)
	{
		philo[i].id_philo = i + 1;
		philo[i].time_execution = get_time();
		philo[i].program = program;
		philo[i].program->al_live = 1;
		philo[i].left_fork = &program->forks[i];
		philo[i].right_fork = &program->forks[((i + 1) % philo->program->n_philos)];
			// pthread_mutex_init(&program->forks[i].mutexFork, NULL);
		i++;
	}
	return (0);
}
