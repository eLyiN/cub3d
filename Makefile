# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/29 08:42:07 by aarribas          #+#    #+#              #
#    Updated: 2022/08/29 08:53:33 by aarribas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d
CFLAGS	=	-Wall -Werror -Wextra
LIN_FL	=	-ldl -lglfw -pthread -lm
MAC_FL	=	-lglfw -L "/Users/aarribas/.brew/Cellar/glfw/3.3.8/lib"
LIBMLX	=	./libs/MLX42
LIBFT	=	./libs/libft

HEADERS	=	-I ./includes -I $(LIBMLX)/include -I $(LIBFT)
SRCS	=	$(shell find ./srcs -iname "*.c")
OBJS	=	${SRCS:.c=.o}