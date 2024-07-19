/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:46:07 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/19 06:58:09 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <pthread.h>
#include <stdlib.h>

/* Check that program was called with the required number of parameters.
 */
static
int	_validate_argc(int argc)
{
	if (argc != 5 && argc != 6)
	{
		(void)log_fatal(ERR_MSG_WRONG_ARGC);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* argv_checks.c */
int	_parse_num_philos_arg(char const *arg, t_params *params);
int	_parse_time_to_die_arg(char const *arg, t_params *params);
int	_parse_time_to_eat_arg(char const *arg, t_params *params);
int	_parse_time_to_sleep_arg(char const *arg, t_params *params);
int	_parse_min_eat_arg(char const *arg, t_params *params);

/* Parse each parameter individually and initialize simulation parameters.
 *
 * This function depends on _validate_argc.
 */
static
int	_parse_argv(
	char *argv[],
	t_params *params
)
{
	if (argv == NULL)
	{
		return (EXIT_FAILURE);
	}
	if (_parse_num_philos_arg(argv[1], params) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (_parse_time_to_die_arg(argv[2], params) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (_parse_time_to_eat_arg(argv[3], params) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (_parse_time_to_sleep_arg(argv[4], params) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (_parse_min_eat_arg(argv[5], params) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* Initialize the mutexes for logging, initial thread
 * synchronization, and for the stop variable that is
 * used to determine if the simulation has ended.
 */
static
int	_init_mutexes(t_params *params)
{
	if (pthread_mutex_init(&params->log_mtx, NULL) != 0)
	{
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&params->sync_mtx, NULL) != 0)
	{
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&params->stop_mtx, NULL) != 0)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* init_from_env.c */
int	_init_params_from_env(char *envp[], t_params *params);

/* Set loglevel and validate & initalize simulation parameters.
 */
extern
int	init_params(
	int argc,
	char *argv[],
	char *envp[],
	t_params *params
)
{
	if (argv == NULL || params == NULL)
	{
		return (EXIT_FAILURE);
	}
	if (_init_params_from_env(envp, params) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (_validate_argc(argc) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (_parse_argv(argv, params) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	if (_init_mutexes(params) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	params->stop = FALSE;
	return (EXIT_SUCCESS);
}
