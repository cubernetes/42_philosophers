/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:47:17 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/15 20:54:01 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H	1

/******************************** includes ************************************/
# include <stddef.h>

/********************************* defines ************************************/
/********************************* enums **************************************/
enum e_ansi
{
	BLACK		= 0,		/* --+                                */
	RED			= 1,		/*   |                                */
	GREEN		= 2,		/*   |                                */
	ORANGE		= 3,		/*   |                                */
	BLUE		= 4,		/*   +-- first 3 bits determine color */
	MEGANTA		= 5,		/*   |                                */
	CYAN		= 6,		/*   |                                */
	WHITE		= 7,		/* --+                                */
	BOLD		= 1 << 3,	/* combinable */
	ITALIC		= 1 << 4,	/* combinable */
	UNDERLINE	= 1 << 5,	/* combinable */
	SLOW_BLINK	= 1 << 6,	/* combinable */
};

enum e_log_lvl
{
	GET_LOG_LVL	= 1 << 0,
	FATAL		= 1 << 1,
	WARNING		= 1 << 2,
	INFO		= 1 << 3,
	DEBUG		= 1 << 4,
};

/********************************** prototypes ********************************/
/* init */
void	init(int argc, char *argv[]);

/* logging */
int		set_log_lvl(enum e_log_lvl new_log_lvl);
int		get_log_lvl(void);
int		logger(const char *msg, enum e_ansi ansi, enum e_log_lvl log_lvl);

/* misc */
void	print_usage(void);

/* libft-utils */
size_t	ft_strlen(char const *s);
char	*ft_strchr(const char *s, int c);

size_t	ft_strlcpy(char *dst, char const *src, size_t size);
size_t	ft_strlcat(char *dst, char const *src, size_t size);

char	*ft_strtrim(char const *s, char const *set);
char	*ft_strtrim_free_1(char const *s, char const *set);
char	*ft_strtrim_free_2(char const *s, char const *set);
char	*ft_strtrim_free_12(char const *s, char const *set);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free_1(char const *s1, char const *s2);
char	*ft_strjoin_free_2(char const *s1, char const *s2);
char	*ft_strjoin_free_12(char const *s1, char const *s2);
char	*ft_strdup(char const *s);
char	*ft_strdup_free(char const *s);

#endif /* philosophers.h */
