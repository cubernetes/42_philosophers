/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:44:00 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/20 20:01:01 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include <stddef.h>

/* Compare two string until they differ OR len is reached, at which point
 * the ASCII value difference of the characters will be returned.
 */
int	ft_strncmp(char const *s1, char const *s2, size_t len)
{
	unsigned char	*us1;
	unsigned char	*us2;

	if (len == 0)
	{
		return (0);
	}
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (*us1 != '\0' && *us2 != '\0' && *us1 == *us2 && --len)
	{
		us1++;
		us2++;
	}
	if (*us1 != *us2)
	{
		return ((*us1 - *us2 != 0) * (-2 * (*us1 - *us2 < 0) + 1));
	}
	return (0);
}
