/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:55 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/20 00:08:08 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdio.h>
#include <stdlib.h>

/* Returns a malloc'd, semicolon delimited string of
 * ANSI escape sequence attributes, specifically for color.
 */
static
char	*_build_color(enum e_ansi ansi)
{
	char	*color;

	if ((ansi & 7) != 0)
		color = ft_itoa(30 + (ansi & 7));
	else
		color = ft_itoa(90);
	return (color);
}

/* Returns a malloc'd, semicolon delimited string of
 * ANSI escape sequence attributes.
 */
static
char	*_build_attrs(enum e_ansi ansi)
{
	char		*attrs;
	char const	*ansi_code;

	attrs = ft_strdup("");
	if (attrs == NULL)
		return (NULL);
	ansi_code = "";
	if (ansi & BOLD)
		ansi_code = ";1";
	if (ansi & ITALIC)
		ansi_code = ";3";
	if (ansi & UNDERLINE)
		ansi_code = ";4";
	if (ansi & INVERT)
		ansi_code = ";7";
	attrs = ft_strjoin_free_1(attrs, ansi_code);
	if (attrs == NULL)
		return (NULL);
	return (attrs);
}

/* Log a given msg to stdout, respecting the log level and color settings.
 */
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
	if (ansi == NO_CLR)
		return (printf("%s\n", msg));
	color = _build_color(ansi);
	if (color == NULL)
		return (-1);
	attrs = _build_attrs(ansi);
	if (attrs == NULL)
	{
		safe_free(color);
		return (-1);
	}
	ret = printf("\033[%s%sm%s\033[m\n", color, attrs, msg);
	safe_free(color);
	safe_free(attrs);
	return (ret);
}

/* Log a given msg to stdout without a newline,
 * respecting the log level and color settings.
 */
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
	if (ansi == NO_CLR)
		return (printf("%s", msg));
	color = _build_color(ansi);
	if (color == NULL)
		return (-1);
	attrs = _build_attrs(ansi);
	if (attrs == NULL)
	{
		safe_free(color);
		return (-1);
	}
	ret = printf("\033[%s%sm%s\033[m", color, attrs, msg);
	safe_free(color);
	safe_free(attrs);
	return (ret);
}
