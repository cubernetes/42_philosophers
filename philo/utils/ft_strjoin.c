/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:45:01 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 19:58:59 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "utils.h"

#include <stdlib.h>

/* Join two C-strings, returning another heap-allocated NUL-terminated string.
 * Not freeing any arguments.
 */
char	*ft_strjoin(
	char const *s1,
	char const *s2
)
{
	size_t	total_len;
	char	*joined_str;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc(sizeof(*joined_str) * (total_len + 1));
	if (joined_str == NULL)
		return (NULL);
	ft_strlcat(joined_str, s1, total_len + 1);
	ft_strlcat(joined_str, s2, total_len + 1);
	return (joined_str);
}

/* Join two C-strings, returning another heap-allocated NUL-terminated string.
 * Freeing the first argument.
 */
char	*ft_strjoin_free_1(
	char const *s1,
	char const *s2
)
{
	size_t	total_len;
	char	*joined_str;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc(sizeof(*joined_str) * (total_len + 1));
	ft_bzero(joined_str, total_len + 1);
	if (joined_str == NULL)
	{
		free((char *)s1);
		return (NULL);
	}
	ft_strlcat(joined_str, s1, total_len + 1);
	ft_strlcat(joined_str, s2, total_len + 1);
	free((char *)s1);
	return (joined_str);
}

/* Join two C-strings, returning another heap-allocated NUL-terminated string.
 * Freeing the second argument.
 */
char	*ft_strjoin_free_2(
	char const *s1,
	char const *s2
)
{
	size_t	total_len;
	char	*joined_str;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc(sizeof(*joined_str) * (total_len + 1));
	if (joined_str == NULL)
	{
		free((char *)s2);
		return (NULL);
	}
	ft_strlcat(joined_str, s1, total_len + 1);
	ft_strlcat(joined_str, s2, total_len + 1);
	free((char *)s2);
	return (joined_str);
}

/* Join two C-strings, returning another heap-allocated NUL-terminated string.
 * Freeing both arguments.
 */
char	*ft_strjoin_free_12(
	char const *s1,
	char const *s2
)
{
	size_t	total_len;
	char	*joined_str;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc(sizeof(*joined_str) * (total_len + 1));
	if (joined_str == NULL)
	{
		free((char *)s1);
		free((char *)s2);
		return (NULL);
	}
	ft_strlcat(joined_str, s1, total_len + 1);
	ft_strlcat(joined_str, s2, total_len + 1);
	free((char *)s1);
	free((char *)s2);
	return (joined_str);
}
