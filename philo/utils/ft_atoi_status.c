/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 23:21:55 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 02:44:36 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

static void	_parse_tail(
	char const *nptr,
	int *status
)
{
	if (*nptr != '\0')
		*status |= STATUS_NO_TRAIL_NUL;
	while (*nptr)
	{
		if (*nptr != ' ' && *nptr != '\n' && *nptr != '\t')
			*status |= STATUS_NO_TRAIL_WHITE;
		++nptr;
	}
}

static int	_ft_atoi_status_neg(
	char const *nptr,
	int *status
)
{
	int	res;
	int	prev_res;

	res = 0;
	prev_res = 0;
	if (ft_isdigit(*nptr) == 0)
		*status |= STATUS_EMPTY_STR;
	while (ft_isdigit(*nptr))
	{
		res = res * 10 - (*nptr - '0');
		if (res > prev_res)
			*status |= STATUS_OVERFLOW;
		prev_res = res;
		++nptr;
	}
	_parse_tail(nptr, status);
	return (res);
}

static int	_ft_atoi_status_pos(
	char const *nptr,
	int *status
)
{
	int	res;
	int	prev_res;

	res = 0;
	prev_res = 0;
	if (ft_isdigit(*nptr) == 0)
		*status |= STATUS_EMPTY_STR;
	while (ft_isdigit(*nptr))
	{
		res = res * 10 + (*nptr - '0');
		if (res < prev_res)
			*status |= STATUS_OVERFLOW;
		prev_res = res;
		++nptr;
	}
	_parse_tail(nptr, status);
	return (res);
}

int	ft_atoi_status(
	char const *nptr,
	int *status
)
{
	*status = 0;
	if (nptr == NULL)
		return (STATUS_NULL_STR);
	while (ft_isspace(*nptr))
		++nptr;
	if (*nptr == '-')
	{
		++nptr;
		return (_ft_atoi_status_neg(nptr, status));
	}
	if (*nptr == '+')
		++nptr;
	return (_ft_atoi_status_pos(nptr, status));
}
