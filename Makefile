# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/26 22:48:41 by rfulop            #+#    #+#              #
#    Updated: 2017/12/07 16:10:20 by rfulop           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
.PHONY: all, clean, fclean, re

CC = clang
CFLAGS = -g -Wall -Werror -Wextra -Wunused
VM_NAME = corewar
ASM_NAME = asm
DASM_NAME = decompiler

SRC_PATH_VM = ./srcs/vm/
SRC_PATH_ASM = ./srcs/asm/
SRC_PATH_DASM = ./srcs/dasm/
OBJ_PATH = ./obj/
OBJ_PATH_VM = ./obj/vm/
OBJ_PATH_ASM = ./obj/asm/
OBJ_PATH_DASM = ./obj/dasm/
INC_PATH = ./includes/
LIB_PATH = ./libft/
BUILD_PATH = ./build/

SRC_FILES_VM = main.c \
								init.c	\
								error.c	\
								check_arg.c	\
								check_ocp.c	\
								controller.c	\
								cycle_to_die.c	\
								check_inst.c	\
								debug.c	\
								aff.c	\
								sti.c	\
								ld.c	\
								ldi.c	\
								lldi.c	\
								live.c	\
								add.c	\
								and.c	\
								free.c	\
								ncurses.c	\
								ncurses_mem.c	\
								ncurses_menu.c	\
								ncurses_breakdown.c	\
								ncurses_get.c	\
								linux.c	\
								pars_op.c	\
								players.c	\
								pc.c	\
								processus.c	\
								pars_players.c	\
								fork.c \
								get_arg.c	\
								lfork.c	\
								or.c \
								xor.c \
								sub.c \
								st.c \
								zjmp.c \
								op.c \
								winner.c \
								tools.c \
								lld.c

SRC_FILES_ASM = main.c \
								create_file.c \
								mode.c \
								error.c \
								error2.c	\
								labels.c \
								header.c \
								debug.c \
								op.c \
								find_op.c \
								parsing_tools.c \
								toolkit.c \
								analyse.c \
								analyse_tools.c \
								display1.c \
								display2.c \
								check_line.c \
								check_header.c \
								lex_ins1.c \
								lex_ins2.c \
								check_arg1.c \
								check_arg2.c \
								read_line.c \
								read_tools.c \
								verbose1.c \
								verbose2.c \
								free.c
SRC_FILES_DASM = main.c \
				op.c \
				error.c \
				file.c \
				get.c \
				display_args.c \


INC_FILES = corewar.h
LIB_FILES = libft.a
LIB = $(addprefix $(LIB_PATH), $(LIB_FILES))

OBJ_FILES_VM = $(SRC_FILES_VM:.c=.o)
OBJ_FILES_ASM = $(SRC_FILES_ASM:.c=.o)
OBJ_FILES_DASM = $(SRC_FILES_DASM:.c=.o)
OBJ_EXEC_VM = $(addprefix $(OBJ_PATH_VM), $(OBJ_FILES_VM))
OBJ_EXEC_ASM = $(addprefix $(OBJ_PATH_ASM), $(OBJ_FILES_ASM))
OBJ_EXEC_DASM = $(addprefix $(OBJ_PATH_DASM), $(OBJ_FILES_DASM))

all: $(VM_NAME) $(ASM_NAME) $(DASM_NAME)

$(OBJ_PATH_VM):
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH_VM) 2> /dev/null || true

$(OBJ_PATH_ASM):
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH_ASM) 2> /dev/null || true

$(OBJ_PATH_DASM):
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH_DASM) 2> /dev/null || true

$(OBJ_PATH_VM)%.o: $(SRC_PATH_VM)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH) -I $(LIB_PATH)includes
	@echo "\033[34mCompilation of \033[36m$(notdir $<)\033[34m done.\033[0m"

$(OBJ_PATH_ASM)%.o: $(SRC_PATH_ASM)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH) -I $(LIB_PATH)includes
	@echo "\033[34mCompilation of \033[36m$(notdir $<)\033[34m done.\033[0m"

$(OBJ_PATH_DASM)%.o: $(SRC_PATH_DASM)%.c
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

$(DASM_NAME): CREATE_BUILD $(OBJ_PATH_DASM) $(OBJ_EXEC_DASM)
	@make -C $(LIB_PATH)
	@$(CC) $(CFLAGS) $(OBJ_EXEC_DASM) $(LIB) -o build/$(DASM_NAME) -I $(INC_PATH) -I $(LIB_PATH)includes
	@echo "\033[32mBinary \033[1;32m$(DASM_NAME)\033[1;0m\033[32m created.\033[0m"

clean:
	@rm -rf $(OBJ_PATH)
	@rm -rf $(OBJ_PATH_VM)
	@rm -rf $(OBJ_PATH_ASM)
	@rm -rf $(OBJ_PATH_DASM)
	@make -C $(LIB_PATH) clean
	@echo "\033[31mObjects files \033[1;31m$(OBJ_FILES_VM)\033[1;0m\033[31m removed.\033[0m"
	@echo "\033[31mObjects files \033[1;31m$(OBJ_FILES_ASM)\033[1;0m\033[31m removed.\033[0m"
	@echo "\033[31mObjects files \033[1;31m$(OBJ_FILES_DASM)\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@rm -f $(BUILD_PATH)$(VM_NAME)
	@rm -f $(BUILD_PATH)$(ASM_NAME)
	@rm -f $(BUILD_PATH)$(DASM_NAME)
	@rm -rf $(BUILD_PATH)
	@make -C $(LIB_PATH) fclean
	@echo "\033[31mBinary \033[1;31m$(VM_NAME)\033[1;0m\033[31m removed.\033[0m"
	@echo "\033[31mBinary \033[1;31m$(ASM_NAME)\033[1;0m\033[31m removed.\033[0m"
	@echo "\033[31mBinary \033[1;31m$(DASM_NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all
