# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/26 22:48:41 by rfulop            #+#    #+#              #
#    Updated: 2017/10/19 23:23:57 by lchety           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
.PHONY: all, clean, fclean, re

CC = clang
CFLAGS = -g
VM_NAME = corewar
ASM_NAME = asm

SRC_PATH_VM = ./srcs/vm/
SRC_PATH_ASM = ./srcs/asm/
OBJ_PATH = ./obj/
OBJ_PATH_VM = ./obj/vm/
OBJ_PATH_ASM = ./obj/asm/
INC_PATH = ./includes/
LIB_PATH = ./libft/
BUILD_PATH = ./build/

SRC_FILES_VM = main.c \
								init.c	\
								error.c	\
								check_arg.c	\
								controller.c	\
								debug.c	\
								sti.c	\
								ld.c	\
								ldi.c	\
								live.c	\
								add.c	\
								and.c	\
								ncurses.c	\
								pars_op.c	\
								players.c	\
								processus.c	\
								fork.c \
								or.c \
								xor.c \
								sub.c \
								st.c \
								state.c	\
								zjmp.c \
								op.c \

SRC_FILES_ASM = main.c \
								error.c \
								labels.c \
								header.c \
								debug.c \
								op.c \

INC_FILES = corewar.h
LIB_FILES = libft.a
LIB = $(addprefix $(LIB_PATH), $(LIB_FILES))

OBJ_FILES_VM = $(SRC_FILES_VM:.c=.o)
OBJ_FILES_ASM = $(SRC_FILES_ASM:.c=.o)
OBJ_EXEC_VM = $(addprefix $(OBJ_PATH_VM), $(OBJ_FILES_VM))
OBJ_EXEC_ASM = $(addprefix $(OBJ_PATH_ASM), $(OBJ_FILES_ASM))

all: $(VM_NAME) $(ASM_NAME)

$(OBJ_PATH_VM):
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH_VM) 2> /dev/null || true

$(OBJ_PATH_ASM):
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH_ASM) 2> /dev/null || true


$(OBJ_PATH_VM)%.o: $(SRC_PATH_VM)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH) -I $(LIB_PATH)includes
	@echo "\033[34mCompilation of \033[36m$(notdir $<)\033[34m done.\033[0m"

$(OBJ_PATH_ASM)%.o: $(SRC_PATH_ASM)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH) -I $(LIB_PATH)includes
	@echo "\033[34mCompilation of \033[36m$(notdir $<)\033[34m done.\033[0m"

CREATE_BUILD:
	@mkdir $(BUILD_PATH) 2> /dev/null || true

$(VM_NAME): CREATE_BUILD $(OBJ_PATH_VM) $(OBJ_EXEC_VM)
	@make -C $(LIB_PATH)
	@$(CC) $(CFLAGS) $(OBJ_EXEC_VM) $(LIB) -o build/$(VM_NAME) -I $(INC_PATH) -I $(LIB_PATH)includes -lncurses
	@echo "\033[32mBinary \033[1;32m$(VM_NAME)\033[1;0m\033[32m created.\033[0m"

$(ASM_NAME): CREATE_BUILD $(OBJ_PATH_ASM) $(OBJ_EXEC_ASM)
	@make -C $(LIB_PATH)
	@$(CC) $(CFLAGS) $(OBJ_EXEC_ASM) $(LIB) -o build/$(ASM_NAME) -I $(INC_PATH) -I $(LIB_PATH)includes
	@echo "\033[32mBinary \033[1;32m$(ASM_NAME)\033[1;0m\033[32m created.\033[0m"

clean:
	@rm -rf $(OBJ_PATH)
	@rm -rf $(OBJ_PATH_VM)
	@rm -rf $(OBJ_PATH_ASM)
	@make -C $(LIB_PATH) fclean
	@echo "\033[31mObjects files \033[1;31m$(OBJ_FILES_VM)\033[1;0m\033[31m removed.\033[0m"
	@echo "\033[31mObjects files \033[1;31m$(OBJ_FILES_ASM)\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@rm -f $(VM_NAME)
	@rm -f $(ASM_NAME)
	@echo "\033[31mBinary \033[1;31m$(VM_NAME)\033[1;0m\033[31m removed.\033[0m"
	@echo "\033[31mBinary \033[1;31m$(ASM_NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all
