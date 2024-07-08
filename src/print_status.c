/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:41:24 by felperei          #+#    #+#             */
/*   Updated: 2024/07/08 15:41:39 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print_fork(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->program->gate);
	time = (get_time() - philo->program->time_start) % 10000;
	printf(CYN "%ld %d has taken a fork\n" RESET,
			time,
			philo->id_philo);
	pthread_mutex_unlock(&philo->program->gate);
}
void	print_eat(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->program->gate);
	time = (get_time() - philo->program->time_start) % 10000;
	printf(GRN "%ld %d is eating\n" RESET,
			time,
			philo->id_philo);
	pthread_mutex_unlock(&philo->program->gate);
}
void	philo_thinking(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->program->gate);
	time = (get_time() - philo->program->time_start) % 10000;
	printf(BLU "%ld %d is thinking  \n" RESET,
			time,
			philo->id_philo);
	pthread_mutex_unlock(&philo->program->gate);
}

void	philo_sleep(t_philo *philo, t_program *program)
{
	long time;

	pthread_mutex_lock(&philo->program->gate);
	time = (get_time() - program->time_start) % 10000;
	printf(MAG "%ld %d is sleeping\n" RESET,
			time,
			philo->id_philo);
	pthread_mutex_unlock(&philo->program->gate);
	smart_sleep(program, program->time_to_sleep_ms);
}
void	print_died(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->program->gate);
	time = (get_time() - philo->program->time_start) % 10000;
	printf(RED "%ld %d is died\n" RESET,
			time,
			philo->id_philo);
	pthread_mutex_unlock(&philo->program->gate);
}