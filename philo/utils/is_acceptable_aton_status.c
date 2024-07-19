/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_acceptable_aton_status.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 05:31:33 by tischmid          #+#    #+#             */
/*   Updated: 2024/07/19 23:32:03 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* Check if the result of a number conversion (atoi, etc.) was valid enough.
 */
int	is_acceptable_aton_status(int status)
{
	if ((status & (STATUS_OVERFLOW | STATUS_EMPTY_STR | STATUS_NO_TRAIL_WHITE))
		== 0)
		return (TRUE);
	else
		return (FALSE);
}
