# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 14:19:47 by yonuma            #+#    #+#              #
#    Updated: 2024/12/20 11:50:29 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# minilibx_test
NAME		=	minilibx_test
SRCS		=	main.c \
				move.c
OBJS 		=	$(SRCS:.c=.o)
# Compiler
CC			=	cc
LIBX_FLAGS	=	-lmlx_Linux -lXext -lX11

# Rules
all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LIBX_FLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
