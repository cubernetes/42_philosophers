/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_wrappers_nonl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:55 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/16 00:23:21 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

int	log_fatal_nonl(char const *msg)
{
	return (logger_nonl(msg, RED | INVERT | BOLD, FATAL));
}

int	log_error_nonl(char const *msg)
{
	return (logger_nonl(msg, RED | BOLD, ERROR));
}

int	log_warn_nonl(char const *msg)
{
	return (logger_nonl(msg, ORANGE | BOLD, WARN));
}

int	log_info_nonl(char const *msg)
{
	return (logger_nonl(msg, BLUE | BOLD, INFO));
}

int	log_debug_nonl(char const *msg)
{
	return (logger_nonl(msg, GREY | BOLD, DEBUG));
}
