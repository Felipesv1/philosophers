/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felperei <felperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:33:06 by felperei          #+#    #+#             */
/*   Updated: 2024/07/10 09:53:55 by felperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philosophers.h"

void	free_program(t_program *program)
{
	if (program)
	{
		if (program->philosophers)
		{
			free(program->philosophers);
		}
		if (program->forks)
			free(program->forks);
		free(program);
	}
}
