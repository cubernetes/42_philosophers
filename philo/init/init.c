/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:46:07 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 02:40:46 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <pthread.h>
#include <stdlib.h>

/* check that program was called with the required number of parameters */
static int	_argc_check(int argc)
{
	if (argc != 5 && argc != 6)
	{
		(void)log_fatal(ERR_WRONG_ARGC);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* argv_checks.c */
int	_num_philos_check(char const *arg, t_params *params);
int	_time_to_die_check(char const *arg, t_params *params);
int	_time_to_eat_check(char const *arg, t_params *params);
int	_time_to_sleep_check(char const *arg, t_params *params);
int	_min_eat_check(char const *arg, t_params *params);

/* parse each parameter individually and initialize simulation parameters */
/* this function depends on _argc_check */
static int	_argv_check(char *argv[], t_params *params)
{
	if (_num_philos_check(argv[1], params))
		return (EXIT_FAILURE);
	if (_time_to_die_check(argv[2], params))
		return (EXIT_FAILURE);
	if (_time_to_eat_check(argv[3], params))
		return (EXIT_FAILURE);
	if (_time_to_sleep_check(argv[4], params))
		return (EXIT_FAILURE);
	if (_min_eat_check(argv[5], params))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* parse command line arguments to initialize simulation parameters */
static int	_parse_arguments(int argc, char *argv[], t_params *params)
{
	if (_argc_check(argc))
		return (EXIT_FAILURE);
	if (_argv_check(argv, params))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* init_from_env.c */
int	_init_log_lvl(char *envp[]);
int	_init_debug(char *envp[], t_params *params);

/* set loglevel and validate & initalize simulation parameters */
int	init(int argc, char *argv[], char *envp[], t_params *params)
{
	if (_init_debug(envp, params))
		return (EXIT_FAILURE);
	if (_init_log_lvl(envp))
		return (EXIT_FAILURE);
	if (_parse_arguments(argc, argv, params))
		return (EXIT_FAILURE);
	pthread_mutex_init(&params->log_mtx, NULL);
	return (EXIT_SUCCESS);
}
