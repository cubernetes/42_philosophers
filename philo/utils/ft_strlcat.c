/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:53:56 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 03:41:20 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include <stddef.h>

/* Concatenate two C-strings by writing into a pre-allocated buffer,
 * NUL-terminating the result.
 */
size_t	ft_strlcat(
	char *dst,
	char const *src,
	size_t size
)
{
	size_t	idx;
	size_t	src_idx;
	size_t	src_len;
	size_t	dst_len;

	src_len = 0;
	while (src[src_len] != '\0')
		++src_len;
	idx = 0;
	while (dst[idx] != '\0' && idx < size)
		++idx;
	dst_len = idx;
	if (dst_len == size)
		return (src_len + size);
	src_idx = 0;
	size -= dst_len;
	while (size > 1 && src[src_idx] != '\0')
	{
		dst[idx] = src[src_idx];
		++idx;
		++src_idx;
		--size;
	}
	dst[idx] = 0;
	return (dst_len + src_len);
}
