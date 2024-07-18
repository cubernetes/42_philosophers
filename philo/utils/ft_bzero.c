/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:16:57 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 03:39:33 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include <stddef.h>

/* Zero-out a memory region of size n, starting at ptr.
 */
void	ft_bzero(void *ptr, size_t n)
{
	char	*p;

	p = (char *)ptr;
	while (n--)
	{
		*p = '\0';
		++p;
	}
}
