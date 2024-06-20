/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:10:48 by felperei          #+#    #+#             */
/*   Updated: 2024/06/20 15:28:00 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	int				n_fork;
	pthread_mutex_t	mutexFork;
}					t_fork;
struct s_program;

typedef struct s_philo
{
	int				id_philo;
	pthread_t		philo;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long			time_execution;
	struct s_program		*program;
}					t_philo;

typedef struct s_program
{
	t_fork			*forks;
	t_philo			*philosophers;
	int				n_philos;
	int				time_to_eat_ms;
	int				time_to_die_ms;
	int				time_to_sleep_ms;
	int				n_of_times_each_philosopher_must_eat;
	long			time_start;
}					t_program;

// utils philosophers
int					ft_atoi(const char *str);
#endif