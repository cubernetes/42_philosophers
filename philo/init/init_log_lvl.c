/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_log_lvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:40:16 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/15 23:07:56 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

#include <stdlib.h>

/* helper function to set the loglevel from a string */
static int	_set_log_lvl_from_string(char const *s)
{
	if (ft_strcmp(s, "FATAL") == 0)
		(void)set_log_lvl(FATAL);
	else if (ft_strcmp(s, "ERROR") == 0)
		(void)set_log_lvl(ERROR);
	else if (ft_strcmp(s, "WARN") == 0)
		(void)set_log_lvl(WARN);
	else if (ft_strcmp(s, "INFO") == 0)
		(void)set_log_lvl(INFO);
	else if (ft_strcmp(s, "DEBUG") == 0)
		(void)set_log_lvl(DEBUG);
	else
		(void)set_log_lvl(INFO);
	return (EXIT_SUCCESS);
}

/* read the LOGLEVEL environment variable and set the loglevel accordingly */
int	_init_log_lvl(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "LOGLEVEL=", 9) == 0)
			return (_set_log_lvl_from_string(*envp + 9));
		++envp;
	}
	(void)set_log_lvl(INFO);
	return (EXIT_SUCCESS);
}
