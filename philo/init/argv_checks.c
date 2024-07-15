/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 23:05:54 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/15 23:56:15 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

#include <stdlib.h>

/* validate & initalize number_of_philosophers simulation parameter */
int	_num_philos_check(char const *arg, t_params *params)
{
	int	status;

	params->num_philos = ft_atoi_status(arg, &status);
	if (status & (STATUS_OVERFLOW | STATUS_EMPTY_STR | STATUS_NO_TRAIL_WHITE)
		|| params->num_philos < 0)
	{
		log_fatal(ERR_WRONG_ARG_NUM_PHILOS_1 ERR_WRONG_ARG_NUM_PHILOS_2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* validate & initalize time_to_die simulation parameter */
int	_time_to_die_check(char const *arg, t_params *params)
{
	int	status;

	params->time_to_die = ft_atoi_status(arg, &status);
	if (status & (STATUS_OVERFLOW | STATUS_EMPTY_STR | STATUS_NO_TRAIL_WHITE)
		|| params->time_to_die < 0)
	{
		log_fatal(ERR_WRONG_ARG_TIME_TO_DIE_1 ERR_WRONG_ARG_TIME_TO_DIE_2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* validate & initalize time_to_eat simulation parameter */
int	_time_to_eat_check(char const *arg, t_params *params)
{
	int	status;

	params->time_to_eat = ft_atoi_status(arg, &status);
	if (status & (STATUS_OVERFLOW | STATUS_EMPTY_STR | STATUS_NO_TRAIL_WHITE)
		|| params->time_to_eat < 0)
	{
		log_fatal(ERR_WRONG_ARG_TIME_TO_EAT_1 ERR_WRONG_ARG_TIME_TO_EAT_2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* validate & initalize time_to_sleep simulation parameter */
int	_time_to_sleep_check(char const *arg, t_params *params)
{
	int	status;

	params->time_to_sleep = ft_atoi_status(arg, &status);
	if (status & (STATUS_OVERFLOW | STATUS_EMPTY_STR | STATUS_NO_TRAIL_WHITE)
		|| params->time_to_sleep < 0)
	{
		log_fatal(ERR_WRONG_ARG_TIME_TO_SLEEP_1 ERR_WRONG_ARG_TIME_TO_SLEEP_2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/* validate & initalize number_of_times_each_philosophers_must_each
 * simulation parameter or set it to -1 if it was not specified */
int	_min_eat_check(char const *arg, t_params *params)
{
	int	status;

	if (arg == NULL)
	{
		params->min_eat = -1;
		return (EXIT_SUCCESS);
	}
	params->min_eat = ft_atoi_status(arg, &status);
	if (status & (STATUS_OVERFLOW | STATUS_EMPTY_STR | STATUS_NO_TRAIL_WHITE)
		|| params->min_eat < 0)
	{
		log_fatal(ERR_WRONG_ARG_MIN_EAT_1 \
				ERR_WRONG_ARG_MIN_EAT_2 \
				ERR_WRONG_ARG_MIN_EAT_3);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
