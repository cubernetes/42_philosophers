/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tischmid <tischmid@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:00:00 by tischmid          #+#    #+#             */
/*   Updated: 2024/07/19 23:31:46 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H	1

# include <stddef.h>

# define TRUE 1
# define FALSE 0

/* Possible status flag for "a to n" conversions (e.g. atoi, atol, etc.) */
enum e_aton_status
{
	STATUS_OVERFLOW			= 1 << 0,
	STATUS_NO_TRAIL_NUL		= 1 << 1,
	STATUS_NO_TRAIL_WHITE	= 1 << 2,
	STATUS_EMPTY_STR		= 1 << 3,
	STATUS_NULL_STR			= 1 << 4,
};

extern size_t		ft_strlen(char const *s);
extern char			*ft_strchr(const char *s, int c);

extern size_t		ft_strlcpy(char *dst, char const *src, size_t size);
extern size_t		ft_strlcat(char *dst, char const *src, size_t size);

extern char			*ft_strtrim(char const *s, char const *set);
extern char			*ft_strtrim_free_1(char const *s, char const *set);
extern char			*ft_strtrim_free_2(char const *s, char const *set);
extern char			*ft_strtrim_free_12(char const *s, char const *set);

extern char			*ft_strjoin(char const *s1, char const *s2);
extern char			*ft_strjoin_free_1(char const *s1, char const *s2);
extern char			*ft_strjoin_free_2(char const *s1, char const *s2);
extern char			*ft_strjoin_free_12(char const *s1, char const *s2);

extern char			*ft_strdup(char const *s);
extern char			*ft_strdup_free(char const *s);

extern void			ft_bzero(void *ptr, size_t n);
extern unsigned int	ft_abs(int n);

extern int			ft_strcmp(char const *s1, char const *s2);
extern int			ft_strncmp(char const *s1, char const *s2, size_t len);
extern char			*ft_itoa(int n);

extern int			ft_isspace(int c);
extern int			ft_isdigit(int c);

extern int			ft_atoi_status(char const *nptr, int *status);
extern int			is_acceptable_aton_status(int status);
extern void			safe_free(void *ptr);

#endif /* utils.h */
