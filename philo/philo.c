/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:26 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 19:52:21 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>

/* Welcome to the philosopher project. I tried to make the code as clean
 * as possible, but also be very pedantic (yet structured) about it.
 * This is why you see that EVERY (literally, even printf) function
 * that may fail will be caught, no ignored exit statuses at all,
 * even for the joined threads.
 * Every condition is explicit (strcmp() == 0 instead of !strcmp()).
 * At points where the return value is ignored, there will be a (void) cast.
 * Static functions are prefixed with _ (underscore).
 * Function prototypes are not put into header files when there are only
 * used in a single file (like a static function, but yk, we are only allowed
 * 5 functions per file. They might even have the _ prefix if appropriate).
 *
 * There is unstructured documentation (more like explanatory comments)
 * for every single implemeneted function. Even the low-level utils.
 * At times, there might be more text, when it comes to the algorithm
 * for example and my thought processes.
 * This code base is supposed to be educational, in a sense, also for me.
 */
int	main(
	int argc,
	char *argv[],
	char *envp[]
)
{
	t_params	params;

	if (init(argc, argv, envp, &params) == EXIT_FAILURE)
	{
		(void)print_usage(argv);
		return (EXIT_FAILURE);
	}
	if (simulate(&params) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
