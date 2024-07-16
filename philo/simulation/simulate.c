/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:26 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/16 06:23:17 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <unistd.h>

static int	_wait_for_philos(
	pthread_t *philo_threads,
	t_params *params
)
{
	int	idx;
	int	err;

	err = 0;
	idx = 0;
	while (idx < params->num_philos)
	{
		err += pthread_join(philo_threads[idx], NULL);
		++idx;
	}
	return (err);
}

static void	_cleanup_philos(
	t_philo **philos,
	t_params *params
)
{
	int	idx;

	idx = 0;
	while (idx < params->num_philos)
	{
		free(philos[idx]->right_fork);
		free(philos[idx]);
		++idx;
	}
	free(philos);
}

/* spawn_philos.c */
t_philo	**_spawn_philos(pthread_t *philo_threads, t_params *params);

int	simulate(t_params *params)
{
	pthread_t	*philo_threads;
	t_philo		**philos;

	philo_threads = malloc(sizeof(*philo_threads) * (size_t)params->num_philos);
	philos = _spawn_philos(philo_threads, params);
	(void)_wait_for_philos(philo_threads, params);
	_cleanup_philos(philos, params);
	free(philo_threads);
	return (EXIT_SUCCESS);
}
