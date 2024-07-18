/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:19 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/16 00:27:19 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

/* print how to use this program */
void	print_usage(char *argv[])
{
	(void)log_info_nonl("Usage: ");
	(void)log_info_nonl(argv[0]);
	(void)log_info(" NOP TOD TOE TOS ME");
	(void)log_info("\tNOP := Number of Philosophers");
	(void)log_info("\tTOD := Time to Die");
	(void)log_info("\tTOE := Time to Eat");
	(void)log_info("\tTOS := Time to Sleep");
	(void)log_info("\tME  := Min Eat == Minimum amount all philos have to eat");
	(void)log_info("Examples:");
	(void)log_info_nonl("\t");
	(void)log_info_nonl(argv[0]);
	(void)log_info(" 5 400 200 100");
	(void)log_info_nonl("\t");
	(void)log_info_nonl(argv[0]);
	(void)log_info(" 5 400 200 300 7");
}
