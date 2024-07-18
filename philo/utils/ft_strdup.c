/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:07:41 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/15 20:31:08 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>

/* return a heap-allocated copy of the C-string s.
 * not freeing any arguments.
 */
char	*ft_strdup(char const *s)
{
	char	*res;
	size_t	size;

	size = ft_strlen(s);
	res = malloc(sizeof(*res) * (size + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s, size + 1);
	return (res);
}

/* return a heap-allocated copy of the C-string s.
 * freeing the first argument.
 */
char	*ft_strdup_free(char const *s)
{
	char	*res;
	size_t	size;

	size = ft_strlen(s);
	res = malloc(sizeof(*res) * (size + 1));
	if (res == NULL)
	{
		free((char *)s);
		return (NULL);
	}
	ft_strlcpy(res, s, size + 1);
	free((char *)s);
	return (res);
}
