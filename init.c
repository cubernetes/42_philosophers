/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:46:07 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/15 21:57:51 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

static void	_set_log_lvl_from_string(char const *s)
{
	if (ft_strcmp(s, "FATAL") == 0)
		set_log_lvl(FATAL);
	else if (ft_strcmp(s, "ERROR") == 0)
		set_log_lvl(ERROR);
	else if (ft_strcmp(s, "WARN") == 0)
		set_log_lvl(WARN);
	else if (ft_strcmp(s, "INFO") == 0)
		set_log_lvl(INFO);
	else if (ft_strcmp(s, "DEBUG") == 0)
		set_log_lvl(DEBUG);
	else
		set_log_lvl(INFO);
}

static void	_init_log_lvl(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "LOGLEVEL=", 9) == 0)
		{
			_set_log_lvl_from_string(*envp + 9);
			return ;
		}
		++envp;
	}
	set_log_lvl(INFO);
}

void	init(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	_init_log_lvl(envp);
	print_usage();
}
