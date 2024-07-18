/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:19 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 18:21:32 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"
#include <stdlib.h>

/* Print how to use this program.
 */
int	print_usage(char *argv[])
{
	int	err;

	if (argv == NULL)
		return (EXIT_FAILURE);
	err = 0;
	err |= log_info_nonl("Usage: ") < 0;
	err |= log_info_nonl(argv[0]) < 0;
	err |= log_info(" NOP TOD TOE TOS ME") < 0;
	err |= log_info("\tNOP := Number of Philosophers") < 0;
	err |= log_info("\tTOD := Time to Die") < 0;
	err |= log_info("\tTOE := Time to Eat") < 0;
	err |= log_info("\tTOS := Time to Sleep") < 0;
	err |= log_info("\tME  := Min Eat == Minimum amount all philos have to eat")
		< 0;
	err |= log_info("Examples:") < 0;
	err |= log_info_nonl("\t") < 0;
	err |= log_info_nonl(argv[0]) < 0;
	err |= log_info(" 5 400 200 100") < 0;
	err |= log_info_nonl("\t") < 0;
	err |= log_info_nonl(argv[0]) < 0;
	err |= log_info(" 5 400 200 300 7") < 0;
	if (err != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
