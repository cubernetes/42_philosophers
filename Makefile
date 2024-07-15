# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tosuman <timo42@proton.me>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 20:33:50 by tosuman           #+#    #+#              #
#    Updated: 2024/07/15 20:51:07 by tosuman          ###   ########.fr        #
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
vpath %.c utils
SRC :=
SRC += philo.c
SRC += init.c
SRC += err.c
SRC += logger.c
SRC += ft_strchr.c
SRC += ft_strdup.c
SRC += ft_strjoin.c
SRC += ft_strlcat.c
SRC += ft_strlcpy.c
SRC += ft_strlen.c
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

.PHONY: re fclean clean all
