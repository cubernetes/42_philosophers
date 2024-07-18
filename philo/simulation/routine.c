/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 06:07:17 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 03:51:45 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <pthread.h>
#include <stdio.h>

/* fork_logic.c */
void	_pickup_forks(t_philo *philo);
void	_putdown_forks(t_philo *philo);

/* this is the "idle work" function, where the thread just idly sits and
 * does not need any of the mutually exclusive resources, thereby allowing
 * other threads to use them (forks/chopsticks in our case).
 *
 * If time-to-die is reached inside this function, it will be logged and
 * now further diagnostic messages ought to be printed.
 */
static void	_sleep(t_philo *philo)
{
	log_philo(PHILO_SLEEPING, philo);
	ft_msleep(philo->params->time_to_sleep);
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
static void	_eat(t_philo *philo)
{
	log_philo(PHILO_THINKING, philo);
	_pickup_forks(philo);
	log_philo(PHILO_EATING, philo);
	ft_msleep(philo->params->time_to_eat);
	_putdown_forks(philo);
}

/* Main philosopher routine: eat, think, sleep, repeat, die.
 */
void	*routine(void *philo)
{
	while (1)
	{
		_eat(philo);
		_sleep(philo);
	}
	return (NULL);
}
