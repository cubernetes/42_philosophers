/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:55 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/16 00:23:57 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

#include <stdio.h>
#include <stdlib.h>

/* returns a malloc'd, semicolon delimited string of
 * ANSI escape sequence attributes, specifically for color */
static char	*_build_color(enum e_ansi ansi)
{
	char	*color;

	if ((ansi & 7) != 0)
		color = ft_itoa(30 + (ansi & 7));
	else
		color = ft_itoa(90);
	return (color);
}

/* returns a malloc'd, semicolon delimited string of
 * ANSI escape sequence attributes */
static char	*_build_attrs(enum e_ansi ansi)
{
	char	*attrs;

	attrs = ft_strdup("");
	if (ansi & BOLD)
		attrs = ft_strjoin_free_1(attrs, ";1");
	if (ansi & ITALIC)
		attrs = ft_strjoin_free_1(attrs, ";3");
	if (ansi & UNDERLINE)
		attrs = ft_strjoin_free_1(attrs, ";4");
	if (ansi & INVERT)
		attrs = ft_strjoin_free_1(attrs, ";7");
	return (attrs);
}

/* log a given msg to stdout, respecting the log level and color settings */
int	logger(
	const char *msg,
	enum e_ansi ansi,
	enum e_log_lvl log_lvl
)
{
	int		ret;
	char	*color;
	char	*attrs;

	if (get_log_lvl() > log_lvl)
		return (0);
	color = _build_color(ansi);
	attrs = _build_attrs(ansi);
	ret = printf("\033[%s%sm%s\033[m\n", color, attrs, msg);
	free(color);
	free(attrs);
	return (ret);
}

/* log a given msg to stdout without a newline,
 * respecting the log level and color settings */
int	logger_nonl(
	const char *msg,
	enum e_ansi ansi,
	enum e_log_lvl log_lvl
)
{
	int		ret;
	char	*color;
	char	*attrs;

	if (get_log_lvl() > log_lvl)
		return (0);
	color = _build_color(ansi);
	attrs = _build_attrs(ansi);
	ret = printf("\033[%s%sm%s\033[m", color, attrs, msg);
	free(color);
	free(attrs);
	return (ret);
}
