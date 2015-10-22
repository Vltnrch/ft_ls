# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroche <vroche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/18 15:45:03 by vroche            #+#    #+#              #
#    Updated: 2015/10/21 20:09:55 by vroche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIB = -L./libft -lft

HDR = -I./libft/includes

FLAGS = -Wall -Wextra -Werror -g

C =	ft_check_opt.c \
	ft_display.c \
	ft_display_prepare.c \
	ft_list.c \
	ft_ls.c \
	ft_manage.c \
	ft_mode.c \
	ft_sort.c \
	main.c

O = $(C:.c=.o)

all: $(NAME)

$(NAME): $(O)
	make -C ./libft
	gcc $(FLAGS) $(HDR) $(LIB) $(O) -o $(NAME)

%.o:%.c
	gcc $(FLAGS) $(HDR) -c $<

clean:
	make -C ./libft clean
	rm -f $(O)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
