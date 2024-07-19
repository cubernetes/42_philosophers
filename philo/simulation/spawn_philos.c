/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 06:06:15 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/20 00:09:55 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>
#include <pthread.h>

/* Create a new fork on the heap, initializing its corresponding mutex.
 */
static t_fork	*_new_fork(unsigned int id)
{
	t_fork	*fork;

	fork = malloc(sizeof(*fork));
	if (fork == NULL)
		return (NULL);
	fork->id = id;
	if (pthread_mutex_init(&fork->mutex, NULL) != 0)
	{
		safe_free(fork);
		return (NULL);
	}
	return (fork);
}

/* Initialize a single new philosopher using a given right fork.
 * The left fork is either created (on the heap) or set to the first
 * fork if we are at the last philosopher.
 */
static t_philo	*_init_philo(unsigned int id, t_params *params,
	t_fork *right_fork, t_fork *first_fork)
{
	t_philo	*philo;

	if (params == NULL || right_fork == NULL)
		return (NULL);
	philo = malloc(sizeof(*philo));
	if (philo == NULL)
		return (NULL);
	philo->params = params;
	philo->right_fork = right_fork;
	if (pthread_mutex_init(&philo->last_meal_mtx, NULL) != 0)
		return (safe_free(philo), NULL);
	if (id == (unsigned int)params->num_philos - 1)
		philo->left_fork = first_fork;
	else
	{
		philo->left_fork = _new_fork(id);
		if (philo->left_fork == NULL)
		{
			safe_free(philo);
			return (NULL);
		}
	}
	philo->id = id;
	return (philo);
}

/* Helper to free the philos pointer (just the pointer) and the first_fork
 * fork. 
 */
static void	_cleanup_philos_fork(t_philo **philos, t_fork *first_fork)
{
	safe_free(philos);
	if (first_fork != NULL)
	{
		pthread_mutex_destroy(&first_fork->mutex);
		safe_free(first_fork);
	}
}

/* Helper to prepare the data structures used for spawning
 * the philosopher threads.
 */
static t_philo	**_prepare_philo_spawning(t_params *params, t_fork **first_fork,
	t_philo **first_philo)
{
	t_philo			**philos;

	philos = malloc(sizeof(*philos) * (size_t)params->num_philos);
	if (philos == NULL)
		return (NULL);
	ft_bzero(philos, sizeof(*philos) * (size_t)params->num_philos);
	*first_fork = _new_fork((unsigned int)params->num_philos - 1);
	if (*first_fork == NULL)
	{
		_cleanup_philos_fork(philos, *first_fork);
		return (NULL);
	}
	params->start_time = 0;
	*first_philo = _init_philo(0, params, *first_fork, *first_fork);
	if (*first_philo == NULL)
	{
		_cleanup_philos_fork(philos, *first_fork);
		return (NULL);
	}
	return (philos);
}

/* routine.c */
void	*routine(void *data);

/* Create and return a heap-allocated array of philosopher structs,
 * each containing (e.g.) 2 pointers, one for the left fork, one for the
 * right fork, where adjacent philosophers share the same pointer to a fork.
 *
 * Additionally, create <number of philosophers> threads, passing the
 * philosopher as the void-ptr to the "routine" function (the entry point
 * to the thread). This has to be done reasonably fast to avoid delays
 * in starting times.
 */
t_philo	**_spawn_philos(pthread_t *philo_threads, t_params *params)
{
	unsigned int	idx;
	t_philo			*philo;
	t_philo			**philos;
	t_fork			*first_fork;

	if (philo_threads == NULL || params == NULL)
		return (NULL);
	idx = 0;
	philos = _prepare_philo_spawning(params, &first_fork, &philo);
	if (philos == NULL || first_fork == NULL || philo == NULL)
		return (NULL);
	philos[idx] = philo;
	while (TRUE)
	{
		if (pthread_create(philo_threads + idx, NULL, routine, philo) != 0)
			return (cleanup_philos(philos, params), NULL);
		++idx;
		if (idx >= (unsigned int)params->num_philos)
			break ;
		philo = _init_philo(idx, params, philo->left_fork, first_fork);
		if (philo == NULL)
			return (cleanup_philos(philos, params), NULL);
		philos[idx] = philo;
	}
	return (philos);
}
/* This algorithm can probably we written more elegantly, for example
 * recursively, like [@nlaerema]
 * (https://github.com/kodokaii/Philosophers/blob/master/philo/start.c)
 * did.
 */
