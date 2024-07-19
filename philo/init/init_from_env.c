/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_from_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:40:16 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/19 23:54:03 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>

/* Helper function to set the loglevel from a string.
 */
static int	_set_log_lvl_from_str(char const *s)
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

/* Read the LOGLEVEL environment variable and set the loglevel accordingly.
 */
static int	_init_log_lvl(char *envp[])
{
	while (envp != NULL && *envp != NULL)
	{
		if (ft_strncmp(*envp, "LOGLEVEL=", ft_strlen("LOGLEVEL=")) != 0)
		{
			++envp;
			continue ;
		}
		*envp += ft_strlen("LOGLEVEL=");
		return (_set_log_lvl_from_str(*envp));
	}
	(void)set_log_lvl(INFO);
	return (EXIT_SUCCESS);
}

/* Read the DEBUG environment variable and set the debug flag accordingly.
 */
static int	_init_debug(char *envp[], t_params *params)
{
	while (envp != NULL && *envp != NULL)
	{
		if (ft_strncmp(*envp, "DEBUG=", ft_strlen("DEBUG=")) != 0)
		{
			++envp;
			continue ;
		}
		*envp += ft_strlen("DEBUG=");
		if (ft_strcmp(*envp, "1") == 0)
		{
			params->debug = TRUE;
		}
		else
		{
			params->debug = FALSE;
		}
		return (EXIT_SUCCESS);
	}
	params->debug = FALSE;
	return (EXIT_SUCCESS);
}

/* Initialize parameters than can be set from the environment.
 */
int	_init_params_from_env(char *envp[], t_params *params)
{
	if (_init_debug(envp, params) || _init_log_lvl(envp))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
