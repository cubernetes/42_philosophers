/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:19 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/19 23:56:10 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>

/* Internal helper that determines if any given log attempt failed.
 * It will not immediately abort, but rather execute every log attempt.
 * Only at the end, failure will be returned and must be handled by the caller.
 */
static int	_print_usage_internal(char *const program_name)
{
	if (log_info_nonl("Usage: ") < 0
		|| log_info_nonl(program_name) < 0
		|| log_info(" NOP TOD TOE TOS ME") < 0
		|| log_info("\tNOP := Number of Philosophers (please <= 200 :})") < 0
		|| log_info("\tTOD := Time to Die") < 0
		|| log_info("\tTOE := Time to Eat") < 0
		|| log_info("\tTOS := Time to Sleep") < 0
		|| log_info("\tME  := Min Eat == Min meals all philos have to eat") < 0
		|| log_info("Examples:") < 0
		|| log_info_nonl("\t") < 0
		|| log_info_nonl(program_name) < 0
		|| log_info(" 5 400 200 100") < 0
		|| log_info_nonl("\t") < 0
		|| log_info_nonl(program_name) < 0
		|| log_info(" 15 400 200 300 7") < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* Print how to use this program.
 */
int	print_usage(char *argv[])
{
	if (argv == NULL
		|| _print_usage_internal(argv[0]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
