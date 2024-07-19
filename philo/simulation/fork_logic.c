/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 03:06:58 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/19 04:25:47 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>

/* Philosophers are sitting around a round table with sequential integer
 * identifiers. If the identifier is ODD (id % 2 != 0, the first branch),
 * then a mutex ought to be locked FIRST for the right fork, THEN for the left
 * fork. If the identifier is EVEN (id % 2 == 0, the second branch), then
 * the order of locking ought to be REVERSED.
 *
 * This breaks the 4th coffman condition, hence preventing deadlocks.
 * Additionally, it prevents starvation in general (unlike when assigning a
 * partial order). However, it does not distribute blocking times fairly among
 * threads. The philosohper with the lowest id generally has to wait longer than
 * the one with the highest id. This is explained superficially in this link:
 * https://web.eecs.utk.edu/~mbeck/classes/cs560/560/notes/Dphil/lecture.html
 * Cf. solution 4.
 */
int	_pickup_forks(t_philo *philo)
{
	if (philo == NULL)
		return (EXIT_FAILURE);
	if (philo->id % 2 == 1)
	{
		if (pthread_mutex_lock(&philo->right_fork->mutex) != 0)
			return (EXIT_FAILURE);
		if (log_philo(PHILO_FORK, philo) == EXIT_FAILURE)
		{
			(void)pthread_mutex_unlock(&philo->right_fork->mutex);
			return (EXIT_FAILURE);
		}
		if (pthread_mutex_lock(&philo->left_fork->mutex) != 0)
			return (EXIT_FAILURE);
		if (log_philo(PHILO_FORK, philo) == EXIT_FAILURE)
		{
			(void)pthread_mutex_unlock(&philo->left_fork->mutex);
			(void)pthread_mutex_unlock(&philo->right_fork->mutex);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (pthread_mutex_lock(&philo->left_fork->mutex) != 0)
			return (EXIT_FAILURE);
		if (log_philo(PHILO_FORK, philo) == EXIT_FAILURE)
		{
			(void)pthread_mutex_unlock(&philo->left_fork->mutex);
			return (EXIT_FAILURE);
		}
		if (pthread_mutex_lock(&philo->right_fork->mutex) != 0)
			return (EXIT_FAILURE);
		if (log_philo(PHILO_FORK, philo) == EXIT_FAILURE)
		{
			(void)pthread_mutex_unlock(&philo->right_fork->mutex);
			(void)pthread_mutex_unlock(&philo->left_fork->mutex);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/* Release the locks for the forks in the reverse manner as they were acquired.
 * I don't know if the order makes a difference, but I've heard that it doesn't.
 */
int	_putdown_forks(t_philo *philo)
{
	if (philo == NULL)
		return (EXIT_FAILURE);
	if (philo->id % 2 == 1)
	{
		if (pthread_mutex_unlock(&philo->left_fork->mutex) != 0)
			return (EXIT_FAILURE);
		if (pthread_mutex_unlock(&philo->right_fork->mutex) != 0)
			return (EXIT_FAILURE);
	}
	else
	{
		if (pthread_mutex_unlock(&philo->right_fork->mutex) != 0)
			return (EXIT_FAILURE);
		if (pthread_mutex_unlock(&philo->left_fork->mutex) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
