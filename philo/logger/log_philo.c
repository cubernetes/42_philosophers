/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 02:48:02 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 02:56:09 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>

static enum e_ansi	_get_philo_log_clr(enum e_philo_log log)
{
	if (log == PHILO_SLEEPING)
		return (BLUE);
	else if (log == PHILO_THINKING)
		return (GREEN);
	else if (log == PHILO_EATING)
		return (MAGENTA);
	else if (log == PHILO_FORK)
		return (ORANGE);
	return (RED | INVERT);
}

static char	*_get_philo_log_msg(enum e_philo_log log)
{
	if (log == PHILO_SLEEPING)
		return (PHILO_SLEEPING_MSG);
	else if (log == PHILO_THINKING)
		return (PHILO_THINKING_MSG);
	else if (log == PHILO_EATING)
		return (PHILO_EATING_MSG);
	else if (log == PHILO_FORK)
		return (PHILO_FORK_MSG);
	return ("has done something extraordinary...");
}

void	log_philo(enum e_philo_log log, t_philo *philo)
{
	char		*offset;
	char		*id;
	enum e_ansi	log_lvl;

	if (philo->params->debug)
		log_lvl = _get_philo_log_clr(log) | BOLD;
	else
		log_lvl = NO_CLR;
	offset = ft_itoa((int)(get_mtime() - philo->params->start_time));
	id = ft_itoa((int)philo->id + 1);
	pthread_mutex_lock(&philo->params->log_mtx);
	logger_nonl(offset, log_lvl, INFO);
	logger_nonl(" ", log_lvl, INFO);
	logger_nonl(id, log_lvl, INFO);
	logger_nonl(" ", log_lvl, INFO);
	logger(_get_philo_log_msg(log), log_lvl, INFO);
	pthread_mutex_unlock(&philo->params->log_mtx);
	free(offset);
	free(id);
}
