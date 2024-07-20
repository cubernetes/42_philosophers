/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:52:45 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/20 17:53:24 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* this is the "idle work" function, where the thread just idly sits and
 * does not need any of the mutually exclusive resources, thereby allowing
 * other threads to use them (forks/chopsticks in our case).
 *
 * If time-to-die is reached inside this function, it will be logged and
 * now further diagnostic messages ought to be printed.
 */
int	_sleep(t_philo *philo)
{
	if (philo == NULL)
		return (EXIT_FAILURE);
	if (log_philo(PHILO_SLEEPING, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_msleep(philo->params->time_to_sleep) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	_think(t_philo *philo)
{
	if (philo == NULL)
		return (EXIT_FAILURE);
	if (log_philo(PHILO_THINKING, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_msleep(philo->params->time_to_think) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* This is the "resource work" function, where a thread occupies ("holds")
 * the mutually exclusive resource (in this case, forks/chopsticks).
 * The logic in "pickup" and "putdown" is the important bit. This implementation
 * uses the "every other philosopher picks up their forks right-then-left
 * instead of left-then-right". This, however, does not distribute the resources
 * in a fair manner, see the following link (solution #4):
 * https://web.eecs.utk.edu/~mbeck/classes/cs560/560/notes/Dphil/lecture.html
 * In the context of the subject, we do not care about equal blocking times,
 * and since this solution is surprisingly simple/elegant, I'm gonna keep it
 * this way.
 *
 * If time-to-die is reached inside this function, it will be logged and
 * now further diagnostic messages ought to be printed.
 */
int	_eat(t_philo *philo)
{
	if (philo == NULL)
		return (EXIT_FAILURE);
	if (_pickup_forks(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (log_philo(PHILO_EATING, philo) == EXIT_FAILURE)
		return (_putdown_forks(philo), EXIT_FAILURE);
	if (pthread_mutex_lock(&philo->meal_mtx) != 0)
		return (_putdown_forks(philo), EXIT_FAILURE);
	philo->last_meal = get_mtime();
	--philo->eat_credit;
	if (pthread_mutex_unlock(&philo->meal_mtx) != 0
		|| philo->last_meal == 0)
		return (_putdown_forks(philo), EXIT_FAILURE);
	if (ft_msleep(philo->params->time_to_eat) == EXIT_FAILURE)
		return (_putdown_forks(philo), EXIT_FAILURE);
	if (_putdown_forks(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
