/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:12:59 by felperei          #+#    #+#             */
/*   Updated: 2024/06/24 13:57:07 by felperei         ###   ########.fr       */
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