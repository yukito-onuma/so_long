# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 14:19:47 by yonuma            #+#    #+#              #
#    Updated: 2025/01/08 17:00:31 by yonuma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# minilibx_test
NAME		=	minilibx_test
NAME_BONUS	=	minilibx_test_bonus
SRCS		=	main.c \
				move.c 
SRCS_BONUS	=	main_bonus.c \
				move.c
OBJS 		=	$(SRCS:.c=.o)
OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)
# Compiler
CC			=	cc
LIBX_FLAGS	=	-lXext -lX11 libmlx/libmlx_Linux.a libmlx/libmlx.a -lm -lz

# Rules
all:		$(NAME)

bonus:      $(NAME_BONUS)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LIBX_FLAGS) -o $(NAME)

$(NAME_BONUS)    : $(OBJS_BONUS)
			$(CC) $(OBJS_BONUS) $(LIBX_FLAGS) -o $(NAME_BONUS)

clean:
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			$(RM) $(NAME) $(NAME_BONUS)

re:			fclean all

.PHONY:		all clean fclean re
