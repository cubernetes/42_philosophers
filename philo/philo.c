/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:32:26 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/19 23:37:56 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#include "philo.h"

static int	_main_err(t_err *err, char *argv[])
{
	if (err->err & (1 << 0))
		(void)print_usage(argv);
	return (err->err);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_params	params;
	t_err		err;

	err_wrap_init(&err);
	wrap_err(&err, init(argc, argv, envp, &params));
	wrap_err(&err, !err.err && simulate(&params));
	return (_main_err(&err, argv));
}
