# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 16:53:06 by ezhou             #+#    #+#              #
#    Updated: 2024/02/28 18:00:59 by ezhou            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

LIBFT = libft.a
RM = rm -f

CC = gcc -g -Wall -Wextra -Werror

NAME = pipex
SRC = pipex.c ft_find_path.c ft_process_args.c ft_full_clear.c ft_execute.c \
ft_split_awk.c ft_here_doc.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) -o $(NAME) $(LIBFT) $(OBJ) 
	@echo "$(COLOUR_GREEN)(•̀ᴗ•́)و $(NAME) generado!$(COLOUR_END)"

%.o : %.c
	@$(CC) -c -o $@ $<
	@echo "$(COLOUR_BLUE)(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compilando archivos .c$(COLOUR_END)" 

$(LIBFT):
	@echo "$(COLOUR_BLUE)Compilando libft...$(COLOUR_END)"
	@$(MAKE) -C ./libft
	@cp ./libft/$(LIBFT) ./
	@cp ./libft/libft.h ./
	@echo "$(COLOUR_GREEN)Libft compilada!$(COLOUR_END)"
clean:
	@$(RM) $(OBJ)
	@echo "$(COLOUR_RED)¯\_(ツ)_/¯ Objectos removidos!$(COLOUR_RED)"

fclean: clean
	@$(RM) $(NAME) $(LIBFT) libft.h
	@echo "$(COLOUR_RED)(╯°□°）╯︵ ┻━┻ $(NAME) removido!$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re 