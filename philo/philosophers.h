/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:47:17 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/16 00:24:07 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H	1

/******************************** includes ************************************/
# include <stddef.h>

/********************************* defines ************************************/
# define ERR_WRONG_ARGC "FATAL: Wrong number of arguments. Expected 4 or 5."

# define ERR_WRONG_ARG_NUM_PHILOS_1 "FATAL: Error in parsing the argument "
# define ERR_WRONG_ARG_NUM_PHILOS_2 "specifying the number of philosophers."

# define ERR_WRONG_ARG_TIME_TO_DIE_1 "FATAL: Error in parsing the argument "
# define ERR_WRONG_ARG_TIME_TO_DIE_2 "specifying the time to die."

# define ERR_WRONG_ARG_TIME_TO_EAT_1 "FATAL: Error in parsing the argument "
# define ERR_WRONG_ARG_TIME_TO_EAT_2 "specifying the time to eat."

# define ERR_WRONG_ARG_TIME_TO_SLEEP_1 "FATAL: Error in parsing the argument "
# define ERR_WRONG_ARG_TIME_TO_SLEEP_2 "specifying time to sleep."

# define ERR_WRONG_ARG_MIN_EAT_1 "FATAL: Error in parsing the argument "
# define ERR_WRONG_ARG_MIN_EAT_2 "specifying the minimum number of meals requ"
# define ERR_WRONG_ARG_MIN_EAT_3 "ired per philosopher to end the simulation."

/********************************* enums **************************************/
enum e_ansi
{
	GREY		= 0,		/* --+                                */
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
	INVERT		= 1 << 6,	/* combinable */
};

/* fine grained log levels may be specified */
enum e_log_lvl
{
	GET_LOG_LVL	= 0,
	DEBUG		= 10,
	INFO		= 20,
	WARN		= 30,
	ERROR		= 40,
	FATAL		= 50,
};

/* Possible status flag for "a to n" conversions (e.g. atoi, atol, etc.) */
enum e_aton_status
{
	STATUS_OVERFLOW			= 1 << 0,
	STATUS_NO_TRAIL_NUL		= 1 << 1,
	STATUS_NO_TRAIL_WHITE	= 1 << 2,
	STATUS_EMPTY_STR		= 1 << 3,
	STATUS_NULL_STR			= 1 << 4,
};

/*********************************** structs **********************************/
typedef struct s_params
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_eat;
}	t_params;

/********************************** prototypes ********************************/
int				simulate(t_params *params);
int				init(int argc, char *argv[], char *envp[], t_params **params);

/* logging */
enum e_log_lvl	set_log_lvl(enum e_log_lvl new_log_lvl);
enum e_log_lvl	get_log_lvl(void);
int				logger(const char *msg, enum e_ansi ansi,
					enum e_log_lvl log_lvl);
int				logger_nonl(const char *msg, enum e_ansi ansi,
					enum e_log_lvl log_lvl);
int				log_fatal(char const *msg);
int				log_error(char const *msg);
int				log_warn(char const *msg);
int				log_info(char const *msg);
int				log_debug(char const *msg);
int				log_fatal_nonl(char const *msg);
int				log_error_nonl(char const *msg);
int				log_warn_nonl(char const *msg);
int				log_info_nonl(char const *msg);
int				log_debug_nonl(char const *msg);

/* misc */
void			print_usage(char *argv[]);

/* libft-utils */
size_t			ft_strlen(char const *s);
char			*ft_strchr(const char *s, int c);

size_t			ft_strlcpy(char *dst, char const *src, size_t size);
size_t			ft_strlcat(char *dst, char const *src, size_t size);

char			*ft_strtrim(char const *s, char const *set);
char			*ft_strtrim_free_1(char const *s, char const *set);
char			*ft_strtrim_free_2(char const *s, char const *set);
char			*ft_strtrim_free_12(char const *s, char const *set);

char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free_1(char const *s1, char const *s2);
char			*ft_strjoin_free_2(char const *s1, char const *s2);
char			*ft_strjoin_free_12(char const *s1, char const *s2);

char			*ft_strdup(char const *s);
char			*ft_strdup_free(char const *s);

void			ft_bzero(void *ptr, size_t n);
unsigned int	ft_abs(int n);

int				ft_strcmp(char const *s1, char const *s2);
int				ft_strncmp(char const *s1, char const *s2, size_t len);
char			*ft_itoa(int n);

int				ft_isspace(int c);
int				ft_isdigit(int c);

int				ft_atoi_status(char const *nptr, int *status);

#endif /* philosophers.h */
