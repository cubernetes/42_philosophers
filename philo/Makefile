# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tosuman <timo42@proton.me>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 20:33:50 by tosuman           #+#    #+#              #
#    Updated: 2024/07/16 00:22:57 by tosuman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# ex: set ts=4 sw=4 ft=make noet #

# config
NAME := philo

# tools
CC ?= cc
RM := /bin/rm -f
MKDIR := /bin/mkdir -p

# flags
CFLAGS := -O2 -Wall -Wextra -Werror\
		  -pedantic -Wconversion \
		  -Wunreachable-code -Wshadow
CPPFLAGS := -I. -MMD
LDFLAGS :=
LDLIBS := -lpthread
ifeq ($(DEBUG), 1)
	CFLAGS += -ggdb3 -O0
	LDFLAGS += -ggdb3 -O0
endif

# sources
SRC :=
SRC += philo.c
SRC += simulate.c
SRC += usage.c

vpath %.c init
SRC += init.c
SRC += init_log_lvl.c
SRC += argv_checks.c

vpath %.c logger
SRC += logger.c
SRC += log_level.c
SRC += log_wrappers.c
SRC += log_wrappers_nonl.c

vpath %.c utils
SRC += ft_abs.c
SRC += ft_atoi_status.c
SRC += ft_bzero.c
SRC += ft_isdigit.c
SRC += ft_isspace.c
SRC += ft_itoa.c
SRC += ft_strchr.c
SRC += ft_strcmp.c
SRC += ft_strdup.c
SRC += ft_strjoin.c
SRC += ft_strlcat.c
SRC += ft_strlcpy.c
SRC += ft_strlen.c
SRC += ft_strncmp.c
SRC += ft_strtrim.c

# object variables
OBJ := $(SRC:.c=.o)
OBJDIR = obj
OBJ := $(addprefix $(OBJDIR)/,$(OBJ))

# dependencies
DEPS := $(OBJ:.o=.d)
-include $(DEPS)

# rules
.DEFAULT_GOAL := all

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $(OBJ) $(LDLIBS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -c -o $@ $(CFLAGS) $(CPPFLAGS) $<

$(OBJDIR):
	$(MKDIR) $@

clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	valgrind --track-fds=yes ./philo 1 2 3 4 5

.PHONY: re fclean clean all run
