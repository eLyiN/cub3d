# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarribas <aarribas@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/29 08:42:07 by aarribas          #+#    #+#              #
#    Updated: 2022/09/01 17:59:08 by aarribas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d
CFLAGS	=	-Wall -Werror -Wextra
LIN_FL	=	-ldl -lglfw -pthread -lm
MAC_FL	=	-lglfw -L "/Users/aarribas/.brew/Cellar/glfw/3.3.8/lib"
LIBMLX	=	./libs/MLX42
LIBFT	=	./libs/libft

HEADERS	=	-I ./includes -I $(LIBMLX)/include -I $(LIBFT)
LIBS	=	$(LIBMLX)/libmlx42.a $(LIBFT)/libft.a
SRCS	=	$(shell find ./srcs -iname "*.c")
OBJS	=	${SRCS:.c=.o}

all : libmlx libft $(NAME)

libmlx : 
		$(MAKE) -C $(LIBMLX)

libft : 
		$(MAKE) -C $(LIBFT)

$(NAME) : $(OBJS)
		@$(CC) $(OBJS) $(LIBS) $(CFLAGS) $(LIN_FL) -o $(NAME)

clean :
		@rm -rf $(OBJS)
		@$(MAKE) -C $(LIBFT) clean
		@$(MAKE) -C $(LIBMLX) clean

fclean : clean
		@rm -rf $(NAME)
		@$(MAKE) -C $(LIBFT) fclean
		@$(MAKE) -C $(LIBMLX) fclean

re : clean all

.PHONY: all, clean, fclean, re, libmlx, libft, bonus