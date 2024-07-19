/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:46:07 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/19 23:54:24 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <pthread.h>
#include <stdlib.h>

/* Check that program was called with the required number of parameters.
 */
static int	_validate_argc(int argc)
{
	if (argc != 5 && argc != 6)
	{
		(void)log_fatal(ERR_MSG_WRONG_ARGC);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* Parse each parameter individually and initialize simulation parameters.
 *
 * This function depends on _validate_argc.
 */
static int	_parse_argv(char *argv[], t_params *params)
{
	if (argv == NULL
		|| _parse_num_philos_arg(argv[1], params)
		|| _parse_time_to_die_arg(argv[2], params)
		|| _parse_time_to_eat_arg(argv[3], params)
		|| _parse_time_to_sleep_arg(argv[4], params)
		|| _parse_min_eat_arg(argv[5], params))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* Initialize the mutexes for logging, initial thread
 * synchronization, and for the stop variable that is
 * used to determine if the simulation has ended.
 */
static int	_init_mutexes(t_params *params)
{
	if (pthread_mutex_init(&params->log_mtx, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&params->sync_mtx, NULL))
	{
		pthread_mutex_destroy(&params->log_mtx);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&params->stop_mtx, NULL))
	{
		pthread_mutex_destroy(&params->log_mtx);
		pthread_mutex_destroy(&params->sync_mtx);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* Set loglevel and validate & initalize simulation parameters.
 */
int	init(int argc, char *argv[], char *envp[], t_params *params)
{
	if (argv == NULL
		|| params == NULL
		|| _init_params_from_env(envp, params)
		|| _validate_argc(argc)
		|| _parse_argv(argv, params)
		|| _init_mutexes(params))
		return (EXIT_FAILURE);
	params->stop = FALSE;
	return (EXIT_SUCCESS);
}
