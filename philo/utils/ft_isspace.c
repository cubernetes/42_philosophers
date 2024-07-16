/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 23:23:40 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/16 01:36:28 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

/* return a non-zero integer if the argument is one of the 6 POSIX whitespace */
int	ft_isspace(int c)
{
	return (c == ' '
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\f'
		|| c == '\v');
}
