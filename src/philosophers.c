/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:12:59 by felperei          #+#    #+#             */
/*   Updated: 2024/06/26 08:30:17 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	free_program(t_program *program)
{
	int i;
	i = 0;
	if (program)
	{
		if (program->philosophers)
		{
			if (program->philosophers[i].philo)
			{
				free(program->philosophers);
				i++;
			}
			free(program->philosophers);
		}
		if (program->forks)
			free(program->forks);
		free(program);
	}
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