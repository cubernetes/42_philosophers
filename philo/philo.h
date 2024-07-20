/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:47:17 by tosuman           #+#    #+#             */
/*   Updated: 2024/07/20 22:03:59 by tischmid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ex: set ts=4 sw=4 ft=c et */

#ifndef PHILO_H
# define PHILO_H	1

/******************************** includes ************************************/
# include "utils.h"

# include <sys/time.h>
# include <pthread.h>

/********************************* defines ************************************/
# define ERR_MSG_WRONG_ARGC "FATAL: Wrong number of arguments. Expected 4 or 5."

# define ERR_MSG_WRONG_ARG_NUM_PHILOS "FATAL: Error in parsing the argument \
specifying the number of philosophers (argument 1, 'NOP')."

# define ERR_MSG_WRONG_ARG_TIME_TO_DIE "FATAL: Error in parsing the argument \
specifying the time to die (argument 2, 'TOD')."

# define ERR_MSG_WRONG_ARG_TIME_TO_EAT "FATAL: Error in parsing the argument \
specifying the time to eat (argument 3, 'TOE')."

# define ERR_MSG_WRONG_ARG_TIME_TO_SLEEP "FATAL: Error in parsing the argument \
specifying time to sleep (argument 4, 'TOS')."

# define ERR_MSG_WRONG_ARG_MIN_EAT "FATAL: Error in parsing the argument \
specifying the minimum number of meals required per philosopher \
to end the simulation (argument 5, 'ME')."

# define PHILO_SLEEPING_MSG "is sleeping"
# define PHILO_THINKING_MSG "is thinking"
# define PHILO_EATING_MSG   "is eating"
# define PHILO_FORK_MSG     "has taken a fork"
# define PHILO_DEAD_MSG     "died"

# define ERR_GETTIMEOFDAY 0

/********************************* enums **************************************/
enum e_ansi
{
	GREY		= 0,		/* --+                                */
	RED			= 1,		/*   |                                */
	GREEN		= 2,		/*   |                                */
	ORANGE		= 3,		/*   |                                */
	BLUE		= 4,		/*   +-- first 3 bits determine color */
	MAGENTA		= 5,		/*   |                                */
	CYAN		= 6,		/*   |                                */
	WHITE		= 7,		/* --+                                */
	BOLD		= 1 << 3,	/* combinable */
	ITALIC		= 1 << 4,	/* combinable */
	UNDERLINE	= 1 << 5,	/* combinable */
	INVERT		= 1 << 6,	/* combinable */
	NO_CLR		= 1 << 7,	/* !mutually exlusive to all over values! */
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

enum e_philo_log
{
	PHILO_SLEEPING	= 0,
	PHILO_THINKING	= 1,
	PHILO_EATING	= 2,
	PHILO_FORK		= 3,
	PHILO_DEAD		= 4,
};

/*********************************** structs **********************************/
typedef struct s_params
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				min_eat;
	time_t			start_time;
	int				debug;
	int				stop;
	int				finished_philos;
	pthread_mutex_t	log_mtx;
	pthread_mutex_t	sync_mtx;
	pthread_mutex_t	stop_mtx;
	pthread_mutex_t	finished_philos_mtx;
}	t_params;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	unsigned int	id;
}	t_fork;

typedef struct s_philo
{
	unsigned int	id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				keep_going;
	t_params		*params;
	time_t			last_meal;
	pthread_mutex_t	meal_mtx;
	int				eat_credit;
}	t_philo;

typedef struct s_err
{
	int	err;
	int	id;
}	t_err;

/********************************** prototypes ********************************/
/* simulation */
int				simulate(t_params *params);
int				cleanup_philos(t_philo **philos);
int				sim_has_ended(t_params *params);

/* ft_time.c */
int				ft_msleep(int ms);
time_t			get_mtime(void);

/* logger.c */
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
int				log_philo(enum e_philo_log log, t_philo *philo);

/* usage.c */
int				print_usage(char *argv[]);

/* init.c */
int				init(int argc, char *argv[], char *envp[], t_params *params);

/* err.c */
void			wrap_err(t_err *err, int ret);
void			err_wrap_init(t_err *err);
int				wrap_assign(int ret);

/* argv_checks.c */
int				_parse_num_philos_arg(char const *arg, t_params *params);
int				_parse_time_to_die_arg(char const *arg, t_params *params);
int				_parse_time_to_eat_arg(char const *arg, t_params *params);
int				_parse_time_to_sleep_arg(char const *arg, t_params *params);
int				_parse_min_eat_arg(char const *arg, t_params *params);

/* init_from_env.c */
int				_init_params_from_env(char *envp[], t_params *params);

/* spawn_philos.c */
t_philo			**_spawn_philos(pthread_t *philo_threads, t_params *params);

/* detect_dead_philosophers.c */
int				_detect_dead_philosophers(t_philo **philos, t_params *params);

/* cleanup_simulation.c */
int				_cleanup_simulation(t_philo **philos, t_params *params,
					pthread_t *philo_threads);

/* fork_logic.c */
int				_pickup_forks(t_philo *philo);
int				_putdown_forks(t_philo *philo);

/* eat_sleep_think.c */
int				_sleep(t_philo *philo);
int				_think(t_philo *philo);
int				_eat(t_philo *philo);

/* routine.c */
int				philos_not_finished(t_params *param);

#endif /* philo.h */
