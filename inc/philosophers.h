/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:10:48 by felperei          #+#    #+#             */
/*   Updated: 2024/06/26 14:52:33 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RESET "\033[0m"

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_program;

typedef struct s_philo
{
	int					id_philo;
	pthread_t			philo;
	long				time_execution;
	long				last_eat;
	int					quantity_eat;
	struct s_program	*program;
}						t_philo;

typedef struct s_program
{
	pthread_mutex_t		*forks;
	t_philo				*philosophers;
	int					n_philos;
	int					al_live;
	long				time_to_eat_ms;
	long				time_to_die_ms;
	long				time_to_sleep_ms;
	long				n_of_times_each_philosopher_must_eat;
	long				time_start;
	pthread_mutex_t		gate;
	pthread_mutex_t		mutex_block;
}						t_program;

// utils philosophers
int						ft_atoi(const char *str);
time_t					get_formatter_time(time_t start_time);
long					get_time(void);
// utils_rotine
void					philo_eat(t_philo *philo);
void					*routine(void *arg);
int						monitory(t_philo *philo);

// utils_forks
void					get_forks(t_philo *philo);
void					release_forks(t_philo *philo);
int						set_forks(t_program *program);

// utils_init
int						init_threads_philo(t_program *program);
int						init_philos(t_program *program);
void					init_program(char **av);
void					free_program(t_program *program);
#endif