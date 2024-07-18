/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:18:29 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 03:42:05 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

#include <stdlib.h>

/* Calculate the size of a C-string after trimming it left and right
 * of the characters in set.
 */
static	size_t	_size_after_trim(
	char const *s,
	char const *set
)
{
	int	idx;
	int	start;
	int	end;

	idx = 0;
	while (s[idx] != '\0' && ft_strchr(set, s[idx]))
		++idx;
	start = idx;
	while (s[idx] != '\0')
		++idx;
	--idx;
	while (idx >= 0 && s[idx] != '\0' && ft_strchr(set, s[idx]))
		--idx;
	end = idx;
	return ((size_t)(end - start + 1));
}

/* Trim a C-string left and right of the characters in set,
 * returning the heap-allocated result.
 * Free no arguments.
 */
char	*ft_strtrim(
	char const *s,
	char const *set
)
{
	size_t	trimmed_size;
	char	*trimmed_str;
	int		idx;

	trimmed_size = _size_after_trim(s, set);
	trimmed_str = malloc(sizeof(*trimmed_str) * (trimmed_size + 1));
	if (trimmed_str == NULL)
		return (NULL);
	idx = 0;
	while (s[idx] != '\0' && ft_strchr(set, s[idx]))
		++idx;
	ft_strlcpy(trimmed_str, s + idx, trimmed_size + 1);
	return (trimmed_str);
}

/* Trim a C-string left and right of the characters in set,
 * returning the heap-allocated result.
 * Free the first argument.
 */
char	*ft_strtrim_free_1(
	char const *s,
	char const *set
)
{
	size_t	trimmed_size;
	char	*trimmed_str;
	int		idx;

	trimmed_size = _size_after_trim(s, set);
	trimmed_str = malloc(sizeof(*trimmed_str) * (trimmed_size + 1));
	if (trimmed_str == NULL)
	{
		free((char *)s);
		return (NULL);
	}
	idx = 0;
	while (s[idx] != '\0' && ft_strchr(set, s[idx]))
		++idx;
	ft_strlcpy(trimmed_str, s + idx, trimmed_size + 1);
	free((char *)s);
	return (trimmed_str);
}

/* Trim a C-string left and right of the characters in set,
 * returning the heap-allocated result.
 * Free the second argument.
 */
char	*ft_strtrim_free_2(
	char const *s,
	char const *set
)
{
	size_t	trimmed_size;
	char	*trimmed_str;
	int		idx;

	trimmed_size = _size_after_trim(s, set);
	trimmed_str = malloc(sizeof(*trimmed_str) * (trimmed_size + 1));
	if (trimmed_str == NULL)
	{
		free((char *)set);
		return (NULL);
	}
	idx = 0;
	while (s[idx] != '\0' && ft_strchr(set, s[idx]))
		++idx;
	ft_strlcpy(trimmed_str, s + idx, trimmed_size + 1);
	free((char *)set);
	return (trimmed_str);
}

/* Trim a C-string left and right of the characters in set,
 * returning the heap-allocated result.
 * Free both arguments.
 */
char	*ft_strtrim_free_12(
	char const *s,
	char const *set
)
{
	size_t	trimmed_size;
	char	*trimmed_str;
	int		idx;

	trimmed_size = _size_after_trim(s, set);
	trimmed_str = malloc(sizeof(*trimmed_str) * (trimmed_size + 1));
	if (trimmed_str == NULL)
	{
		free((char *)s);
		free((char *)set);
		return (NULL);
	}
	idx = 0;
	while (s[idx] != '\0' && ft_strchr(set, s[idx]))
		++idx;
	ft_strlcpy(trimmed_str, s + idx, trimmed_size + 1);
	free((char *)s);
	free((char *)set);
	return (trimmed_str);
}
