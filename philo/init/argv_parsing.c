/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 23:05:54 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/20 22:05:15 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>

/* Validate & initalize number_of_philosophers simulation parameter.
 */
int	_parse_num_philos_arg(char const *arg, t_params *params)
{
	int	status;

	if (arg == NULL || params == NULL)
		return (EXIT_FAILURE);
	params->num_philos = ft_atoi_status(arg, &status);
	if (is_acceptable_aton_status(status) && params->num_philos >= 0)
		return (EXIT_SUCCESS);
	(void)log_fatal(ERR_MSG_WRONG_ARG_NUM_PHILOS);
	return (EXIT_FAILURE);
}

/* Validate & initalize time_to_die simulation parameter.
 */
int	_parse_time_to_die_arg(char const *arg, t_params *params)
{
	int	status;

	if (arg == NULL || params == NULL)
		return (EXIT_FAILURE);
	params->time_to_die = ft_atoi_status(arg, &status);
	if (is_acceptable_aton_status(status) && params->time_to_die >= 0)
		return (EXIT_SUCCESS);
	(void)log_fatal(ERR_MSG_WRONG_ARG_TIME_TO_DIE);
	return (EXIT_FAILURE);
}

/* Validate & initalize time_to_eat simulation parameter.
 */
int	_parse_time_to_eat_arg(char const *arg, t_params *params)
{
	int	status;

	if (arg == NULL || params == NULL)
		return (EXIT_FAILURE);
	params->time_to_eat = ft_atoi_status(arg, &status);
	if (is_acceptable_aton_status(status) && params->time_to_eat >= 0)
		return (EXIT_SUCCESS);
	(void)log_fatal(ERR_MSG_WRONG_ARG_TIME_TO_EAT);
	return (EXIT_FAILURE);
}

/* Validate & initalize time_to_sleep simulation parameter.
 */
int	_parse_time_to_sleep_arg(char const *arg, t_params *params)
{
	int	status;

	if (arg == NULL || params == NULL)
		return (EXIT_FAILURE);
	params->time_to_sleep = ft_atoi_status(arg, &status);
	if (is_acceptable_aton_status(status) && params->time_to_sleep >= 0)
		return (EXIT_SUCCESS);
	(void)log_fatal(ERR_MSG_WRONG_ARG_TIME_TO_SLEEP);
	return (EXIT_FAILURE);
}

/* Validate & initalize number_of_times_each_philosophers_must_each
 * simulation parameter or set it to -1 if it was not specified.
 */
int	_parse_min_eat_arg(char const *arg, t_params *params)
{
	int	status;

	if (params == NULL)
		return (EXIT_FAILURE);
	if (arg == NULL)
	{
		params->min_eat = -1;
		return (EXIT_SUCCESS);
	}
	params->min_eat = ft_atoi_status(arg, &status);
	if (is_acceptable_aton_status(status) && params->min_eat > 0)
		return (EXIT_SUCCESS);
	(void)log_fatal(ERR_MSG_WRONG_ARG_MIN_EAT);
	return (EXIT_FAILURE);
}
