/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:26 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/20 19:00:31 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

/* Return the current epoch in milliseconds.
 *
 * A return value of 0 indicates an error.
 */
time_t	get_mtime(void)
{
	struct timeval	tv_now;

	if (gettimeofday(&tv_now, NULL))
		return (ERR_GETTIMEOFDAY);
	return (tv_now.tv_usec / 1000 + tv_now.tv_sec * 1000);
}

/* Sleep for ms milliseconds. Not sure wether just usleep or gradual
 * spinlocking using gettimeofday is better, for now usleep works quite well...
 */
int	ft_msleep(int ms)
{
	if (usleep((unsigned int)ms * 1000))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
