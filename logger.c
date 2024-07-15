/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:49:55 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/15 20:54:24 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

#include <stdio.h>
#include <stdlib.h>

int	set_log_lvl(enum e_log_lvl new_log_lvl)
{
	static enum e_log_lvl	log_level;

	if (new_log_lvl != GET_LOG_LVL)
		log_level = new_log_lvl;
	return (log_level);
}

int	get_log_lvl(void)
{
	return (set_log_lvl(GET_LOG_LVL));
}

int	logger(
	const char *msg,
	enum e_ansi ansi,
	enum e_log_lvl log_lvl
)
{
	int		ret;
	int		color;
	char	*attrs;

	(void)log_lvl;
	color = 30 + (ansi & 7);
	attrs = ft_strdup("");
	if (ansi & BOLD)
		attrs = ft_strjoin_free_1(attrs, ";1");
	if (ansi & ITALIC)
		attrs = ft_strjoin_free_1(attrs, ";3");
	if (ansi & UNDERLINE)
		attrs = ft_strjoin_free_1(attrs, ";4");
	if (ansi & SLOW_BLINK)
		attrs = ft_strjoin_free_1(attrs, ";5");
	attrs = ft_strtrim_free_1(attrs, ";");
	ret = printf("\033[%d%sm%s\033[m\n", 30 + color, attrs, msg);
	free(attrs);
	return (ret);
}
