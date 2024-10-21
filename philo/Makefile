# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brappo <brappo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 12:21:10 by mhotting          #+#    #+#              #
#    Updated: 2024/03/25 11:19:56 by brappo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GENERAL
NAME					=	philo
CC						=	cc
ifndef NOFLAGS
	CFLAGS				=	-Wall -Werror -Wextra -pthread -g3
endif
HFLAGS					=	-I$(HEADERS_DIR)
MAKEFILE				= Makefile

# HEADERS
HEADERS_DIR				=	includes/
HEADERS_FILES			=	philosophers.h
HEADERS					=	$(addprefix $(HEADERS_DIR), $(HEADERS_FILES))

# SOURCES GENERAL
SRCS_MAIN_DIR			=	srcs/
SRCS_FILES				=	main.c \
							utils.c \
							init.c \
							philosopher_utils.c \
							philo_routine.c \
							time_utils.c \
							check_starvation.c \
							last_meal.c \
							create_philosopher.c \
							philo_actions.c
SRCS					=	$(addprefix $(SRCS_MAIN_DIR), $(SRCS_FILES))

# OBJECTS GENERAL
OBJS_MAIN_DIR			=	objs/
OBJS_FILES				=	$(SRCS_FILES:.c=.o)
OBJS					=	$(addprefix $(OBJS_MAIN_DIR), $(OBJS_FILES))

# DEPENDENCIES
DEPS_MAIN_DIR			=	deps/
DEPS_FILES				=	$(OBJS_FILES:.o=.d)
DEPS					=	$(addprefix $(DEPS_MAIN_DIR), $(DEPS_FILES))

#################################################

# RULES
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(HFLAGS) $(OBJS) -o $@

$(OBJS_MAIN_DIR)%.o: $(SRCS_MAIN_DIR)%.c $(HEADERS) $(MAKEFILE)
	@mkdir -p $(@D)
	@mkdir -p $(DEPS_MAIN_DIR)$(dir $*)
	$(CC) $(CFLAGS) $(HFLAGS) -MP -MMD -MF $(DEPS_MAIN_DIR)$*.d -c $< -o $@ 

-include $(DEPS)

clean:
	rm -rf $(OBJS_MAIN_DIR)
	rm -rf $(DEPS_MAIN_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re FORCE
