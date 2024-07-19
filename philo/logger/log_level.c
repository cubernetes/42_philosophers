/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_level.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:17:06 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/19 06:57:01 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

/* Set the log level, which must not be equal to GET_LOG_LVL.
 */
enum e_log_lvl	set_log_lvl(enum e_log_lvl new_log_lvl)
{
	static enum e_log_lvl	log_level;

	if (new_log_lvl != GET_LOG_LVL)
		log_level = new_log_lvl;
	return (log_level);
}

/* Return the current log level.
 */
enum e_log_lvl	get_log_lvl(void)
{
	return (set_log_lvl(GET_LOG_LVL));
}
