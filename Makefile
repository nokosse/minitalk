# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvisouth <kvisouth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 13:40:46 by kvisouth          #+#    #+#              #
#    Updated: 2023/03/09 14:28:43 by kvisouth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for libft, client, and server

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I./includes

# Directories
LIB_DIR = ./libft
OBJ_DIR = ./obj

# Files
LIBFT = $(LIB_DIR)/libft.a
CLIENT = client
SERVER = server

# Source files
CLIENT_SRC = client.c
SERVER_SRC = server.c

# Object files
CLIENT_OBJ = $(OBJ_DIR)/client.o
SERVER_OBJ = $(OBJ_DIR)/server.o

# Targets
.PHONY: all clean fclean re

all: $(CLIENT) $(SERVER)

$(CLIENT): $(LIBFT) $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(CLIENT_OBJ) $(LIBFT)

$(SERVER): $(LIBFT) $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(SERVER_OBJ) $(LIBFT)

$(CLIENT_OBJ): $(CLIENT_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(SERVER_OBJ): $(SERVER_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	make -C $(LIB_DIR) fclean

re: fclean all

# Variables for external use
NAME = minitalk
CLIENT = client
SERVER = server