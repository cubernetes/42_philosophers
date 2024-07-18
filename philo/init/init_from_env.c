/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_from_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:40:16 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 02:45:02 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

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

/* read the DEBUG environment variable and set the debug flag accordingly */
int	_init_debug(char *envp[], t_params *params)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "DEBUG=", 6) == 0)
		{
			params->debug = ft_strcmp(*envp + 6, "1") == 0;
			return (EXIT_SUCCESS);
		}
		++envp;
	}
	params->debug = 0;
	return (EXIT_SUCCESS);
}
