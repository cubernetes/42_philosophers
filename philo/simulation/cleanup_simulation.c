/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 06:15:16 by tischmid          #+#    #+#             */
/*   Updated: 2024/07/20 00:01:07 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdlib.h>

/* Helper for cleanup_philos that iterates over the philos array and
 * free destroys the mutexes, frees the forks, the philosopher, and then
 * finally the array itself.
 */
static int	_free_philos_memory(t_philo **philos, t_params *params,
	int check_num)
{
	int	idx;
	int	err;

	idx = 0;
	err = FALSE;
	while (*philos != NULL && (check_num == 0 || idx < params->num_philos))
	{
		err |= pthread_mutex_destroy(&(*philos)->right_fork->mutex) != 0;
		err |= pthread_mutex_destroy(&(*philos)->last_meal_mtx) != 0;
		safe_free((*philos)->right_fork);
		safe_free(*philos);
		++philos;
		++idx;
	}
	safe_free(philos);
	if (err)
	{
		return (EXIT_FAILURE);
	}
	else
	{
		return (EXIT_SUCCESS);
	}
}

/* Free the memory occupied by the philosopher threads, forks and structs.
 *
 * If params is NULL, philos must be a NULL-terminated array, otherwise
 * the behaviour is undefined.
 *
 * Returns the ptr passed as a parameter (to save lines).
 */
int	cleanup_philos(t_philo **philos, t_params *params)
{
	int	check_num;

	if (philos == NULL)
	{
		return (EXIT_SUCCESS);
	}
	if (params == NULL)
	{
		check_num = 0;
	}
	else
	{
		check_num = 1;
	}
	if (_free_philos_memory(philos, params, check_num) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	else
	{
		return (EXIT_SUCCESS);
	}
}

/* Helper function to free up philosopher array, philosopher threads,
 * and to destroy the mutex.
 *
 * The exit_status (default should be EXIT_SUCCESSS) will be returned
 * unless there is an error with pthread_mutex_destroy.
 */
extern
int	_cleanup_simulation(
	t_philo **philos,
	t_params *params,
	pthread_t *philo_threads
)
{
	int	err;

	safe_free(philo_threads);
	err = FALSE;
	err |= cleanup_philos(philos, params) == EXIT_FAILURE;
	err |= pthread_mutex_destroy(&params->log_mtx) != 0;
	err |= pthread_mutex_destroy(&params->sync_mtx) != 0;
	err |= pthread_mutex_destroy(&params->stop_mtx) != 0;
	if (err)
	{
		return (EXIT_FAILURE);
	}
	else
	{
		return (EXIT_SUCCESS);
	}
}
