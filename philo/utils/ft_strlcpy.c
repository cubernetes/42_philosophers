/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:35:01 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/20 20:00:56 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include <stddef.h>

/* Copy a C-string to another C-string.
 * The resulting string will always be NUL-terminated.
 * size includes the NUL-terminator.
 * Always returns the length of src.
 */
size_t	ft_strlcpy(char *dst, char const *src, size_t size)
{
	size_t	len;

	len = 0;
	while (len + 1 < size && src[len] != '\0')
	{
		*dst = src[len];
		dst++;
		len++;
	}
	if (size != 0)
		*dst = '\0';
	while (src[len] != '\0')
		++len;
	return (len);
}
