# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 19:01:00 by otawatanabe       #+#    #+#              #
#    Updated: 2024/09/11 19:46:54 by otawatanabe      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CC = cc
SRCS = main.c execute.c access.c error.c fork_pipe.c heredoc.c get_next_line.c get_next_line_utils.c
NAME = pipex
OBJS = $(SRCS:.c=.o)
LIB = libft/libft.a
all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $^ $(LIB) -o $@

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus