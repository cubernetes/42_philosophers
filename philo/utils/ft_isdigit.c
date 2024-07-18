/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 23:23:07 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/18 03:40:12 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

/* Return a non-zero integer if the character passed as c is a ASCII digit
 * ('0' to '9').
 */
int	ft_isdigit(int c)
{
	return (2048 * (c >= '0' && c <= '9'));
}
