/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:30:47 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/15 21:43:41 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philosophers.h"

#include <stdlib.h>

/* convert an integer to a heap-allocated C-string */
char	*ft_itoa(int n)
{
	char			*str;
	size_t			n_len;
	unsigned int	n_cpy;
	int				is_neg;

	is_neg = n < 0;
	n_len = 0;
	n_cpy = ft_abs(n) + !n;
	while (n_cpy * ++n_len != 0)
		n_cpy /= 10;
	--n_len;
	str = malloc(sizeof(*str) * (n_len + (size_t)is_neg + 1));
	if (str == NULL)
		return (NULL);
	str += (int)n_len + is_neg;
	n_cpy = ft_abs(n);
	*str-- = 0;
	while (n_len--)
	{
		*str-- = (char)(n_cpy % 10 + '0');
		n_cpy /= 10;
	}
	if (is_neg)
		*str-- = '-';
	return (++str);
}
