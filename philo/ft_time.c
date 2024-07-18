/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:26 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 16:51:15 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include <sys/time.h>
#include <unistd.h>

/* Return the current epoch in milliseconds.
 */
time_t	get_mtime(void)
{
	struct timeval	tv_now;

	(void)gettimeofday(&tv_now, NULL);
	return (tv_now.tv_usec / 1000 + tv_now.tv_sec * 1000);
}

/* Sleep for ms milliseconds. Not sure wether just usleep or gradual
 * spinlocking using gettimeofday is better, for now usleep works quite well...
 */
void	ft_msleep(int ms)
{
	struct timeval	tv_then;
	struct timeval	tv_delta;
	time_t			delay_usec;

	if ((1))
		usleep((unsigned int)ms * 1000);
	else
	{
		delay_usec = ms * 1000;
		(void)gettimeofday(&tv_then, NULL);
		while (1)
		{
			(void)gettimeofday(&tv_delta, NULL);
			if ((tv_delta.tv_sec - tv_then.tv_sec) * 1000000 + tv_delta.tv_usec - tv_then.tv_usec >= delay_usec)
				break ;
			// (void)usleep(10); /* TODO: Try different delays, spinlocking, etc. */
		}
	}
}
