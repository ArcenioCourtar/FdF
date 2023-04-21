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

CC			:=	cc
LIBFT		:=	libft/libft.a
CFLAGS		:=	-Wall -Werror -Wextra
NAME		:=	FdF
OBJFILES	:=	test.o
HEADERFILE	:=	test.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) $(LIBFT) -o $(NAME)

re: fclean all

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJFILES)

fclean:
	$(MAKE) fclean -C libft
	rm -f $(OBJFILES) $(NAME)

%.o: %.c $(HEADERFILE)
	$(CC) -c -g $(CFLAGS) -o $@ $<

$(LIBFT):
	$(MAKE) -C libft

noclutter:
	$(MAKE)
	$(MAKE) clean

fsanitize: $(NAME)
	$(CC) $(CFLAGS) $(OBJFILES) $(LIBFT) -fsanitize=address -o $(NAME)