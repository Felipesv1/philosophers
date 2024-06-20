/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:12:59 by felperei          #+#    #+#             */
/*   Updated: 2024/06/20 15:49:41 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// void	free_program(t_program *program)
// {
// 	if (program)
// 	{
// 		if (program->philosophers)
// 		{
// 			if (program->philosophers->philo)
// 				free(program->philosophers);
// 			free(program->philosophers);
// 		}
// 		if (program->forks)
// 			free(program->forks);
// 		free(program);
// 	}
// }

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// Usa os campos da estrutura program
	// while (1)
	// {
	// if (id_philo % 2 == 0)
	// {
	// 	pthread_mutex_lock(&program->forks].mutexFor[(id_philo - 1)k);
	// 		printf("%d ms Filósofo %d pegou o garfo à sua esquerda\n",
	//                program->time_to_eat_ms, id_philo - 1);
	// 	pthread_mutex_lock(&program->forks[id_philo % id_philo].mutexFork);
	// 	printf("%d ms Filósofo %d pegou o garfo à sua direita\n",
	//                program->time_to_eat_ms, id_philo - 1);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&program->forks[id_philo - 1].mutexFork);
	// 	pthread_mutex_lock(&program->forks[id_philo % id_philo].mutexFork);
	// }
	// pthread_mutex_unlock(&program->forks[(id_philo - 1)].mutexFork);
	// pthread_mutex_unlock(&program->forks[id_philo % id_philo].mutexFork);
	printf("%d ms Philosopher %d is thinking\n", philo->program->time_to_die_ms,
		philo->id_philo);
	printf("%d ms Philosopher %d has  has taken a fork\n",
		philo->program->time_to_eat_ms, philo->id_philo);
	printf("%d ms Philosopher %d is eating\n", philo->program->time_to_eat_ms,
		philo->id_philo);
	// usleep(program->time_to_eat_ms * 1000);
	printf("%d ms Philosopher %d is sleeping\n",
		philo->program->time_to_sleep_ms, philo->id_philo);
	// pthread_mutex_unlock(&program->forks[id_philo].mutexFork);
	// }
	pthread_exit(NULL);
}
int	init_threads_philo(t_program *program)
{
	int	i;

	// int				*id_philo;
	i = 0;
	while (i < program->n_philos)
	{
		// pthread_mutex_init(&program->forks[i].mutexFork, NULL);
		if (pthread_create(&program->philosophers[i].philo, NULL, &routine,
				&program->philosophers[i]) != 0)
		{
			perror("Failed to create thread");
			free(program->philosophers);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < program->n_philos - 1)
	{
		if (pthread_join(program->philosophers[i].philo, NULL) != 0)
		{
			perror("Falha ao esperar pela thread");
			free(program->philosophers);
			return (2);
		}
		i++;
	}
	// pthread_mutex_destroy(&program->forks->mutexFork);
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	time = gettimeofday(&tv, NULL);
	time = ((long)tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("milissegundos: %ld\n", time);
	return (time);
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
	printf("time_execution: %ld\n", philo[i].time_execution);

		philo[i].program = program;
		// pthread_mutex_init(&program->forks[i].mutexFork, NULL);
		i++;
	}
	return (0);
}
void	init_program(char **av)
{
	t_program	*program;

	program = (t_program *)malloc(sizeof(t_program));
	program->n_philos = ft_atoi(av[1]);
	program->forks = (t_fork *)malloc(program->n_philos * sizeof(t_fork));
	program->forks->n_fork = program->n_philos;
	program->philosophers = (t_philo *)malloc(program->n_philos
			* sizeof(t_philo));
	program->time_start = get_time();
	program->time_to_die_ms = ft_atoi(av[2]);
	program->time_to_eat_ms = ft_atoi(av[3]);
	program->time_to_sleep_ms = ft_atoi(av[4]);
	if (av[5])
		program->n_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	printf("sleep : %d\n", program->time_to_sleep_ms);
	init_philos(program);
	init_threads_philo(program);
	// free_program(program);
}
int	main(int ac, char **av)
{
	if (ac < 5)
	{
		printf("Error sintax, missing parameters\n");
		return (1);
	}

	init_program(av);

	return (0);
}