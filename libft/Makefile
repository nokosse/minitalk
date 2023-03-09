# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 17:26:39 by kvisouth          #+#    #+#              #
#    Updated: 2023/01/18 00:32:55 by kvisouth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)
RM	 = rm -rf
AR	 = ar rcs

all:
	@echo -n "\n Compiling 0/$(words $(SRCS)) files"
	@$(MAKE) $(NAME) | awk '{if(NR%2==1){printf "\033[31m\rCompiling %d/%d files\033[0m", NR, $(words $(SRCS))}} END {printf "\033[32m\rCompiled %d/%d files in libft\033[0m\n", NR, NR}'
	@echo "\033[32m>>>>>>>>>>>> Done <<<<<<<<<<<<\n\033[0m"

$(NAME): $(OBJS)
	$(AR) $@ $^

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) obj

fclean:
	@echo "\nRemoving files:\n"
	@$(RM) obj
	@echo "obj"
	@$(RM) $(NAME)
	@echo "$(NAME)\n"

re: fclean all

.PHONY:		all clean fclean re