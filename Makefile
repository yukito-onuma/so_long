# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 14:19:47 by yonuma            #+#    #+#              #
#    Updated: 2024/11/07 21:40:55 by yonuma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long.a
SRCS = main.c
# BONUS = 
	   
OBJS = $(SRCS:.c=.o)
OBJS_B = $(BONUS:.c=.o)
# INCLUDES = -I includes

all : $(NAME)

# bonus : 
# 	@make all "OBJS = $(OBJS) $(OBJS_B)"

$(NAME): $(SRCS)
	make -C libmlx
	$(CC) $(SRCS) -lXext -lX11 libmlx/libmlx_Linux.a libmlx/libmlx.a -lm -lz

clean : 
	rm -f $(OBJS) $(OBJS_B)

fclean : clean
	rm -f $(NAME)

re : fclean all
.PHONY : all clean fclean re