/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:26 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 19:53:15 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <unistd.h>

/* Join the philosophers threads (so they can be cleaned up later).
 */
static int	_wait_for_philos(
	pthread_t *philo_threads,
	t_params *params
)
{
	int		idx;
	int		err;
	void	*ret;

	if (philo_threads == NULL || params == NULL)
		return (EXIT_FAILURE);
	err = 0;
	idx = 0;
	while (idx < params->num_philos)
	{
		err |= pthread_join(philo_threads[idx], &ret) != 0;
		err |= ret != NULL;
		++idx;
	}
	if (err != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* Free the memory occupied by the philosopher threads, forks and structs.
 *
 * If params is NULL, philos must be a NULL-terminated array, otherwise
 * the behaviour is undefined.
 *
 * Returns the ptr passed as a parameter (to save lines).
 */
void	*cleanup_philos(
	t_philo **philos,
	t_params *params,
	void *ptr
)
{
	int	idx;
	int	check_num;

	if (philos == NULL)
		return (ptr);
	check_num = 1;
	if (params == NULL)
		check_num = 0;
	idx = 0;
	while (*philos != NULL && (check_num == 0 || idx < params->num_philos))
	{
		free((*philos)->right_fork);
		free((*philos));
		++philos;
		++idx;
	}
	free(philos);
	return (ptr);
}

/* Helper function to free up philosopher array, philosopher threads,
 * and to destroy the mutex.
 */
static int	_cleanup_simulation(
	t_philo **philos,
	t_params *params,
	pthread_t *philo_threads
)
{
	(void)cleanup_philos(philos, params, NULL);
	if (philo_threads != NULL)
		free(philo_threads);
	if (pthread_mutex_destroy(&params->log_mtx) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* spawn_philos.c */
t_philo	**_spawn_philos(pthread_t *philo_threads, t_params *params);

/* Birds-eye simulation logic:
 * - Spawn philosopher threads
 * - Wait for philosopher threads to finish
 * - Cleanup everything (also in case of error in between)
 */
int	simulate(t_params *params)
{
	pthread_t	*philo_threads;
	t_philo		**philos;
	int			exit_status;

	if (params == NULL)
		return (EXIT_FAILURE);
	exit_status = EXIT_SUCCESS;
	philo_threads = malloc(sizeof(*philo_threads) * (size_t)params->num_philos);
	if (philo_threads == NULL)
		return (EXIT_FAILURE);
	philos = _spawn_philos(philo_threads, params);
	if (philos == NULL)
	{
		(void)_cleanup_simulation(philos, params, philo_threads);
		return (EXIT_FAILURE);
	}
	if (_wait_for_philos(philo_threads, params) == EXIT_FAILURE)
		exit_status = EXIT_FAILURE;
	if (_cleanup_simulation(philos, params, philo_threads) == EXIT_FAILURE)
		exit_status = EXIT_FAILURE;
	return (exit_status);
}
