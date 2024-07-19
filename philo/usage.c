/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:19 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/19 06:58:18 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>

/* Internal helper that determines if any given log attempt failed.
 * It will not immediately abort, but rather execute every log attempt.
 * Only at the end, failure will be returned and must be handled by the caller.
 */
static
int	_print_usage_internal(char *const program_name)
{
	int	err;

	err = FALSE;
	err |= log_info_nonl("Usage: ") < 0;
	err |= log_info_nonl(program_name) < 0;
	err |= log_info(" NOP TOD TOE TOS ME") < 0;
	err |= log_info("\tNOP := Number of Philosophers (please <= 200 :})") < 0;
	err |= log_info("\tTOD := Time to Die") < 0;
	err |= log_info("\tTOE := Time to Eat") < 0;
	err |= log_info("\tTOS := Time to Sleep") < 0;
	err |= log_info("\tME  := Min Eat == Min meals all philos have to eat") < 0;
	err |= log_info("Examples:") < 0;
	err |= log_info_nonl("\t") < 0;
	err |= log_info_nonl(program_name) < 0;
	err |= log_info(" 5 400 200 100") < 0;
	err |= log_info_nonl("\t") < 0;
	err |= log_info_nonl(program_name) < 0;
	err |= log_info(" 15 400 200 300 7") < 0;
	return (err);
}

/* Print how to use this program.
 */
extern
int	print_usage(char *argv[])
{
	if (argv == NULL)
	{
		return (EXIT_FAILURE);
	}
	if (_print_usage_internal(argv[0]) != 0)
	{
		return (EXIT_FAILURE);
	}
	else
	{
		return (EXIT_SUCCESS);
	}
}
