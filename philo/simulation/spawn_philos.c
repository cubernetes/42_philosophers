/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 06:06:15 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 03:48:05 by tosuman          ###   ########.fr       */
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
	fork->id = id;
	pthread_mutex_init(&fork->mutex, NULL);
	return (fork);
}

/* Initialize a single new philosopher using a given right fork.
 * The left fork is either created (on the heap) or set to the first
 * fork if we are at the last philosopher.
 */
static t_philo	*_init_philo(
	unsigned int id,
	t_params *params,
	t_fork *right_fork,
	t_fork *first_fork
)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	philo->params = params;
	philo->right_fork = right_fork;
	if (id == (unsigned int)params->num_philos - 1)
		philo->left_fork = first_fork;
	else
		philo->left_fork = _new_fork(id);
	philo->id = id;
	/* philo->last_meal = get_mtime(); */
	return (philo);
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
t_philo	**_spawn_philos(
	pthread_t *philo_threads,
	t_params *params
)
{
	unsigned int	idx;
	t_philo			*philo;
	t_philo			**philos;
	t_fork			*first_fork;

	idx = 0;
	philos = malloc(sizeof(*philos) * (size_t)params->num_philos);
	first_fork = _new_fork((unsigned int)params->num_philos - 1);
	params->start_time = get_mtime();
	philo = _init_philo(0, params, first_fork, first_fork);
	philos[idx] = philo;
	while (1)
	{
		pthread_create(philo_threads + idx, NULL, routine, philo);
		++idx;
		if (idx >= (unsigned int)params->num_philos)
			break ;
		philo = _init_philo(idx, params, philo->left_fork, first_fork);
		philos[idx] = philo;
	}
	return (philos);
}
/* This algorithm can probably we written more elegantly, for example
 * recursively, like [@nlaerema]
 * (https://github.com/kodokaii/Philosophers/blob/master/philo/start.c)
 * did.
 */
