/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 06:07:17 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/16 06:24:18 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

#include <stdio.h>

/* main philosopher routine: eat, think, sleep, die */
void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	(void)philo;
	printf("HEY, I'M HERE\n");
	return (data);
}
