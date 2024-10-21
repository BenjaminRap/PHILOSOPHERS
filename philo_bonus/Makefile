# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 12:21:10 by mhotting          #+#    #+#              #
#    Updated: 2024/03/24 20:04:10 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GENERAL
NAME					=	philo_bonus
CC						=	cc
ifndef NOFLAGS
	CFLAGS				=	-Wall -Werror -Wextra -pthread -g3
endif
HFLAGS					=	-I$(HEADERS_DIR)
MAKEFILE				= Makefile

# HEADERS
HEADERS_DIR				=	includes/
HEADERS_FILES			=	philosophers_bonus.h
HEADERS					=	$(addprefix $(HEADERS_DIR), $(HEADERS_FILES))

# SOURCES GENERAL
SRCS_MAIN_DIR			=	srcs/
SRCS_FILES				=	main_bonus.c \
							init_bonus.c \
							utils_bonus.c \
							philosophers_bonus.c \
							time_utils_bonus.c \
							philo_routine_bonus.c \
							last_meal_bonus.c \
							check_starvation_bonus.c \
							check_stop_bonus.c \
							philo_actions_bonus.c \
							wait_philosophers_bonus.c
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
