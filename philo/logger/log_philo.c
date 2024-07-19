/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 02:48:02 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/19 07:03:07 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>

/* Return the color code corresponding to the given diagnostic type
 * or inverted red if the type is invalid.
 */
static
enum e_ansi	_get_philo_log_clr(enum e_philo_log log)
{
	if (log == PHILO_SLEEPING)
	{
		return (BLUE);
	}
	else if (log == PHILO_THINKING)
	{
		return (GREEN);
	}
	else if (log == PHILO_EATING)
	{
		return (MAGENTA);
	}
	else if (log == PHILO_FORK)
	{
		return (ORANGE);
	}
	else
	{
		return (RED | INVERT);
	}
}

/* Return the message string corresponding to the given diagnostic type
 * or a bogus message if the type is invalid.
 */
static
char	*_get_philo_log_msg(enum e_philo_log log)
{
	if (log == PHILO_SLEEPING)
	{
		return (PHILO_SLEEPING_MSG);
	}
	else if (log == PHILO_THINKING)
	{
		return (PHILO_THINKING_MSG);
	}
	else if (log == PHILO_EATING)
	{
		return (PHILO_EATING_MSG);
	}
	else if (log == PHILO_FORK)
	{
		return (PHILO_FORK_MSG);
	}
	else
	{
		return ("has done something extraordinary...");
	}
}

/* Helper to free the offset and id strings. Returns with the exit_status
 * passed as a parameter (to save lines).
 */
static
int	_free_offset_id(
	char *offset,
	char *id,
	int exit_status
)
{
	if (offset != NULL)
	{
		safe_free(offset);
	}
	if (id != NULL)
	{
		safe_free(id);
	}
	return (exit_status);
}

/* Just for norminette. Prints the start of a log entry, e.g.
 * "200 3 "
 * without the quotes and without then newline. The message follows immediately.
 */
static
int	_start_log_entry(
	t_philo *philo,
	char *offset,
	char *id,
	enum e_ansi log_lvl
)
{
	if (id == NULL)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(&philo->params->log_mtx) != 0)
		return (EXIT_FAILURE);
	if (sim_has_ended(philo->params) != 0)
	{
		(void)pthread_mutex_unlock(&philo->params->log_mtx);
		return (EXIT_FAILURE);
	}
	if (logger_nonl(offset, log_lvl, INFO) < 0)
	{
		(void)pthread_mutex_unlock(&philo->params->log_mtx);
		return (EXIT_FAILURE);
	}
	if (logger_nonl(" ", log_lvl, INFO) < 0)
	{
		(void)pthread_mutex_unlock(&philo->params->log_mtx);
		return (EXIT_FAILURE);
	}
	if (logger_nonl(id, log_lvl, INFO) < 0)
	{
		(void)pthread_mutex_unlock(&philo->params->log_mtx);
		return (EXIT_FAILURE);
	}
	if (logger_nonl(" ", log_lvl, INFO) < 0)
	{
		(void)pthread_mutex_unlock(&philo->params->log_mtx);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* Print a diagnostic message for a given philosopher, whether they've started
 * eating, sleeping, thinking or picking up a single fork. The printing is
 * protected via a mutex, since otherwise the message will very likely be inter-
 * leaved with other messages (we are making multiple calls to the logger,
 * since we are not allowed to use variadic functions).
 *
 * Unless in debug mode, the output will be plain text without any ANSI-escape
 * sequences. This allows for parsing (we are not allowed to use isatty(3)).
 */
int	log_philo(
	enum e_philo_log log,
	t_philo *philo
)
{
	char		*offset;
	char		*id;
	time_t		now;
	enum e_ansi	log_lvl;

	if (sim_has_ended(philo->params) != 0 || philo == NULL)
	{
		return (EXIT_FAILURE);
	}
	if (philo->params->debug)
	{
		log_lvl = _get_philo_log_clr(log) | BOLD;
	}
	else
	{
		log_lvl = NO_CLR;
	}
	now = get_mtime();
	if (now == 0)
	{
		return (EXIT_FAILURE);
	}
	offset = ft_itoa((int)(now - philo->params->start_time));
	if (offset == NULL)
	{
		return (EXIT_FAILURE);
	}
	id = ft_itoa((int)philo->id + 1);
	if (_start_log_entry(philo, offset, id, log_lvl) == EXIT_FAILURE)
	{
		return (_free_offset_id(offset, id, EXIT_FAILURE));
	}
	if (logger(_get_philo_log_msg(log), log_lvl, INFO) < 0)
	{
		(void)pthread_mutex_unlock(&philo->params->log_mtx);
		return (_free_offset_id(offset, id, EXIT_FAILURE));
	}
	if (pthread_mutex_unlock(&philo->params->log_mtx) != 0)
	{
		return (_free_offset_id(offset, id, EXIT_FAILURE));
	}
	return (_free_offset_id(offset, id, EXIT_SUCCESS));
}
