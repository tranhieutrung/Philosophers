# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 10:07:47 by hitran            #+#    #+#              #
#    Updated: 2024/10/03 15:26:24 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror
INCLUDES 		= -I.
RM 				= rm -rf

# Source files by directory
SRCS			=	main_bonus.c	\
					parse_input_bonus.c	\
					init_philo_bonus.c \
					utils_bonus.c	\
					philo_routine_bonus.c	\
					routine_utils_bonus.c \
					simulate_philo_bonus.c

OBJS			=	$(SRCS:.c=.o)

# Executables
NAME 			= philo

# Targets
all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re