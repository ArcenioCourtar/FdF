# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 18:53:47 by acourtar          #+#    #+#              #
#    Updated: 2023/04/21 18:54:37 by acourtar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
NAME		= $(DIR_BIN)FdF
LIBFT		= $(DIR_LIB)libft.a
MLX			= $(DIR_LIB)libmlx42.a
CFLAGS		= -Wall -Werror -Wextra
SRCFILES	= main.c

DIR_BIN		= bin/
DIR_SRC		= src/
DIR_OBJ		= obj/
DIR_LIB		= lib/

ALL_OBJ		= $(addprefix $(DIR_OBJ), $(SRCFILES:.c=.o))
ALL_SRC		= $(addprefix $(DIR_SRC), $(SRCFILES))

#----------------------------------------------------------------------------

all: $(NAME)

$(NAME): $(LIBFT) $(MLX)
	@mkdir -p $(DIR_BIN)
	$(CC) $(ALL_SRC) $(MLX) $(LIBFT) -Iinclude -Iinclude/MLX42 \
	-ldl -lglfw -pthread -lm -o $(NAME)

re: fclean all

clean:
	$(MAKE) clean -C libft
	rm -rf $(DIR_OBJ) $(DIR_LIB) MLX42/build
	
fclean:
	$(MAKE) fclean -C libft
	rm -rf $(DIR_OBJ) $(DIR_LIB) $(DIR_BIN) MLX42/build

%.o: %.c
	$(CC) -c -g $(CFLAGS) -o $@ $<

$(LIBFT):
	$(MAKE) -C libft
	@mkdir -p $(DIR_LIB)
	mv libft/libft.a $(LIBFT)

$(MLX):
	cd MLX42 && cmake -B build && cd ..
	$(MAKE) -C MLX42/build
	mv MLX42/build/libmlx42.a $(MLX)
	cp -R MLX42/include/MLX42 include/

.PHONY: clean fclean bonus re all