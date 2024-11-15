# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 10:07:47 by hitran            #+#    #+#              #
#    Updated: 2024/10/24 13:55:36 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror
INCLUDES 		= -I.
RM 				= rm -rf

# Source files by directory
SRCS			=	main.c	\
					parse_input.c	\
					init_philo.c \
					utils.c	\
					routine.c	\
					routine_utils.c \
					simulate_philo.c

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