/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:26 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/16 00:17:43 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

#include <stdlib.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_params	*params;

	if (init(argc, argv, envp, &params))
	{
		print_usage(argv);
		free(params);
		return (EXIT_FAILURE);
	}
	if (simulate(params))
	{
		free(params);
		return (EXIT_FAILURE);
	}
	free(params);
	return (EXIT_SUCCESS);
}
