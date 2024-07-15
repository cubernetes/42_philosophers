/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:26 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/16 00:03:33 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_params	*params;

	if (init(argc, argv, envp, &params))
		return (EXIT_FAILURE);
	printf("%d\n", params->num_philos);
	printf("%d\n", params->time_to_die);
	printf("%d\n", params->time_to_eat);
	printf("%d\n", params->time_to_sleep);
	printf("%d\n", params->min_eat);
	free(params);
	return (EXIT_SUCCESS);
}
