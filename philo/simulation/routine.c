/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 06:07:17 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 02:56:57 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

#include <pthread.h>
#include <stdio.h>

static void	_sleep(t_philo *philo)
{
	log_philo(PHILO_SLEEPING, philo);
	ft_msleep(philo->params->time_to_sleep);
}

static void	_pickup_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_philo(PHILO_FORK, philo);
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_philo(PHILO_FORK, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_philo(PHILO_FORK, philo);
		pthread_mutex_lock(&philo->right_fork->mutex);
		log_philo(PHILO_FORK, philo);
	}
}

static void	_putdown_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
	}
}

static void	_eat(t_philo *philo)
{
	log_philo(PHILO_THINKING, philo);
	_pickup_forks(philo);
	log_philo(PHILO_EATING, philo);
	ft_msleep(philo->params->time_to_eat);
	_putdown_forks(philo);
}

/* main philosopher routine: eat, think, sleep, repeat, die */
void	*routine(void *_philo)
{
	t_philo	*philo;

	philo = _philo;
	while (1)
	{
		_eat(philo);
		_sleep(philo);
		/* _think(philo); */
	}
	return (NULL);
}
