/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:26 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/16 05:43:00 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <unistd.h>

t_fork	*_new_fork(unsigned int id)
{
	t_fork	*fork;

	fork = malloc(sizeof(*fork));
	fork->id = id;
	pthread_mutex_init(&fork->mutex, NULL);
	return (fork);
}

t_philo	*_init_philo(unsigned int id, t_fork *right_fork)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	philo->right_fork = right_fork;
	philo->left_fork = _new_fork(id);
	philo->id = id;
	/* philo->last_meal = get_mtime(); */
	return (philo);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	(void)philo;
	printf("HEY, I'M HERE\n");
	return (data);
}

t_philo	**_spawn_philos(pthread_t *philo_threads, t_params *params)
{
	unsigned int	idx;
	t_philo			*philo;
	t_philo			**philos;

	idx = 0;
	philos = malloc(sizeof(*philos) * (size_t)params->num_philos);
	philo = _init_philo(0, _new_fork((unsigned int)params->num_philos - 1));
	philos[idx] = philo;
	while (1)
	{
		pthread_create(philo_threads + idx, NULL, routine, philo);
		++idx;
		if (idx >= (unsigned int)params->num_philos)
			break ;
		philo = _init_philo(idx, philo->left_fork);
		philos[idx] = philo;
	}
	return (philos);
}

int	_wait_for_philos(pthread_t *philo_threads, t_params *params)
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

void	_cleanup_philos(t_philo **philos, t_params *params)
{
	int	idx;

	idx = 0;
	while (idx < params->num_philos)
	{
		free(philos[idx]->right_fork);
		free(philos[idx]);
		++idx;
	}
}

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
