/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:31:18 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/15 21:34:10 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

/* return the unsigned absolute value of the integer n */
unsigned int	ft_abs(int n)
{
	if (n > 0)
		return ((unsigned int)n);
	else
		return (-(unsigned int)n);
}
