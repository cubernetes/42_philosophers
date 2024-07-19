/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:46:07 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/19 23:37:52 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

/* Check that program was called with the required number of parameters.
 */
static int	_validate_argc(int argc)
{
	if (argc != 5 && argc != 6)
	{
		(void)log_fatal(ERR_MSG_WRONG_ARGC);
		return (1);
	}
	return (0);
}

/* Parse each parameter individually and initialize simulation parameters.
 *
 * This function depends on _validate_argc.
 */
static int	_parse_argv(char *argv[], t_params *params)
{
	t_err	err;

	err_wrap_init(&err);
	wrap_err(&err, argv == NULL);
	wrap_err(&err, !err.err && _parse_num_philos_arg(argv[1], params));
	wrap_err(&err, !err.err && _parse_time_to_die_arg(argv[2], params));
	wrap_err(&err, !err.err && _parse_time_to_eat_arg(argv[3], params));
	wrap_err(&err, !err.err && _parse_time_to_sleep_arg(argv[4], params));
	wrap_err(&err, !err.err && _parse_min_eat_arg(argv[5], params));
	return (err.err);
}

/* Initialize the mutexes for logging, initial thread
 * synchronization, and for the stop variable that is
 * used to determine if the simulation has ended.
 */
static int	_init_mutexes(t_params *params)
{
	t_err	err;

	err_wrap_init(&err);
	wrap_err(&err, pthread_mutex_init(&params->log_mtx, NULL));
	wrap_err(&err, !err.err && pthread_mutex_init(&params->sync_mtx, NULL));
	wrap_err(&err, !err.err && pthread_mutex_init(&params->stop_mtx, NULL));
	return (err.err);
}

/* Set loglevel and validate & initalize simulation parameters.
 */
int	init(int argc, char *argv[], char *envp[], t_params *params)
{
	t_err	err;

	err_wrap_init(&err);
	wrap_err(&err, argv == NULL || params == NULL);
	wrap_err(&err, !err.err && _init_params_from_env(envp, params));
	wrap_err(&err, !err.err && _validate_argc(argc));
	wrap_err(&err, !err.err && _parse_argv(argv, params));
	wrap_err(&err, !err.err && _init_mutexes(params));
	params->stop = FALSE;
	return (err.err);
}
