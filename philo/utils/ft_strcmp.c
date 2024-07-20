/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:42:51 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/20 20:00:21 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

/* Compare two string until they differ, at which point the ASCII value
 * difference of the characters will be returned.
 */
int	ft_strcmp(char const *s1, char const *s2)
{
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (*us1 != '\0' && *us2 != '\0' && *us1 == *us2)
	{
		++us1;
		++us2;
	}
	return (*us1 - *us2);
}
