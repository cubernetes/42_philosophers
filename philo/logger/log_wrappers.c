/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_wrappers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:55 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/15 22:35:40 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

int	log_fatal(char const *msg)
{
	return (logger(msg, RED | INVERT | BOLD, FATAL));
}

int	log_error(char const *msg)
{
	return (logger(msg, RED | BOLD, ERROR));
}

int	log_warn(char const *msg)
{
	return (logger(msg, ORANGE | BOLD, WARN));
}

int	log_info(char const *msg)
{
	return (logger(msg, BLUE | BOLD, INFO));
}

int	log_debug(char const *msg)
{
	return (logger(msg, GREY | BOLD, DEBUG));
}
