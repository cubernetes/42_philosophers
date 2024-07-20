/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 06:07:17 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/20 19:23:48 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <limits.h>
#include <stdlib.h>

int	philos_not_finished(t_philo *philo)
{
	int	ret;

	if (pthread_mutex_lock(&philo->params->finished_philos_mtx))
	{
		(void)pthread_mutex_unlock(&philo->params->finished_philos_mtx);
		return (-1);
	}
	ret = philo->params->finished_philos > 0;
	if (pthread_mutex_unlock(&philo->params->finished_philos_mtx))
		return (-1);
	return (ret);
}

static void	*_prepare_routine(void *_philo)
{
	t_philo	*philo;

	if (_philo == NULL)
		return (NULL);
	philo = _philo;
	if (pthread_mutex_lock(&philo->params->sync_mtx))
		return (NULL);
	if (pthread_mutex_unlock(&philo->params->sync_mtx))
		return (NULL);
	if (pthread_mutex_lock(&philo->meal_mtx))
		return (NULL);
	philo->last_meal = get_mtime();
	if (pthread_mutex_unlock(&philo->meal_mtx)
		|| philo->last_meal == 0)
		return (NULL);
	if (log_philo(PHILO_THINKING, philo) == EXIT_FAILURE)
		return (NULL);
	return (philo);
}

static int	_retire_philo(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->meal_mtx))
	{
		(void)pthread_mutex_unlock(&philo->meal_mtx);
		return (EXIT_FAILURE);
	}
	philo->last_meal = LONG_MAX;
	if (pthread_mutex_unlock(&philo->meal_mtx))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	_decrement_eat_credit(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->params->finished_philos_mtx))
	{
		(void)pthread_mutex_unlock(&philo->params->finished_philos_mtx);
		return (EXIT_FAILURE);
	}
	--philo->params->finished_philos;
	if (pthread_mutex_unlock(&philo->params->finished_philos_mtx))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* Main philosopher routine: eat, think, sleep, repeat, die.
 *
 * Do not start until synchronization mutex has been unlocked.
 * This means the main thread can take all the time to create the philo-threads.
 */
void	*routine(void *_philo)
{
	t_philo	*philo;

	philo = _prepare_routine(_philo);
	if (philo == NULL)
		return (NULL);
	if (philo->id % 2)
		ft_msleep(philo->params->time_to_eat / 2);
	while (philos_not_finished(philo))
	{
		if (_eat(philo) == EXIT_FAILURE)
			return (NULL);
		if (_sleep(philo) == EXIT_FAILURE)
			return (NULL);
		if (_think(philo) == EXIT_FAILURE)
			return (NULL);
		if (philo->eat_credit == 0)
			if (_decrement_eat_credit(philo))
				return (NULL);
	}
	if (_retire_philo(philo))
		return (NULL);
	return (philo);
}
