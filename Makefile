# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 14:19:47 by yonuma            #+#    #+#              #
#    Updated: 2024/11/17 18:29:20 by yonuma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# minilibx_test
NAME		=	minilibx_test
SRCS		=	main.c
OBJS 		=	$(SRCS:.c=.o)
# Compiler
CC			=	cc
LIBX_FLAGS	=	-lXext -lX11 -lmlx_Linux

# Rules
all:		$(NAME)

$(NAME):	$(OBJS)
			make -C libmlx
			$(CC) $(OBJS) -Llibmlx $(LIBX_FLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
