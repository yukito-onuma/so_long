# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: su_yu_ <su_yu_@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 14:19:47 by yonuma            #+#    #+#              #
#    Updated: 2025/01/04 18:40:14 by su_yu_           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# minilibx_test
NAME		=	minilibx_test
SRCS		=	main.c \
				move.c
OBJS 		=	$(SRCS:.c=.o)
# Compiler
CC			=	cc
# LIBX_FLAGS	=	-lXext -lX11 libmlx/libmlx_Linux.a libmlx/libmlx.a -lm -lz
LIBX_FLAGS	=	libmlx/libmlx_Linux.a libmlx/libmlx.a -lXext -lX11 -lm -lz

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
