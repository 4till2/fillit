# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yserkez <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/13 14:47:18 by yserkez           #+#    #+#              #
#    Updated: 2018/11/08 17:08:00 by yserkez          ###   ########.fr        #
#    Updated: 2018/10/22 12:49:58 by yserkez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = fillit
SRC = *.c
OBJ = $(SRC:.c=.o)
SRC_PATH = src/
SRC_POS = $(addprefix $(SRC_PATH),$(SRC))
FLAGS = -Wall -Wextra -Werror
LIB = libft/libft.a

all: makelib $(NAME) clean

makelib:
	make all -C libft/

$(NAME):
	gcc $(FLAGS) -o $(NAME) $(SRC_POS) $(LIB);

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all, re, clean, fclean
