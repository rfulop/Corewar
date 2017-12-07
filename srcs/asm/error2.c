/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:38:33 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/05 19:08:18 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	asm_error2(int err, char *str, t_asm_env *env, int column)
{
	if (err == MALLOC_ERR)
		ft_printf("Malloc failed.\n");
	else if (err == INST_ERROR)
		ft_printf("instruction '%s' does not exist.\n", str);
	else if (err == LEX_ERROR)
		ft_printf("lexical error. Waiting for a ',' between arguments.\n");
	else if (err == BAD_ARG_DIR)
		ft_printf("this instruction expected a direct number.\n");
	else if (err == BAD_ARG_REG)
		ft_printf("this instruction expected a register.\n");
	else if (err == BAD_ARG_IND)
		ft_printf(", this instruction expected an index.\n");
	else if (err == BAD_ARG_REG_DIR)
		ft_printf("this instruction expected a direct number or a register.\n");
	else
		asm_error3(err, str, env, column);
}

void	asm_error3(int err, char *str, t_asm_env *env, int column)
{
	int line;

	if (env)
		line = env->line;
	if (err == BAD_ARG_REG_IND)
		ft_printf("this instruction expected a register or an index.\n");
	else if (err == BAD_ARG_IND_DIR)
		ft_printf("this instruction expected an index or a direct number.\n");
	else if (err == BAD_ARG_REG_DIR_IND)
		ft_printf("this instruction expected a reg, a direct or an index.\n");
	else if (err == NO_ARGUMENTS)
		ft_printf("instruction has no arguments\n");
	else if (err == LABEL_ERROR)
		ft_printf("Label '%s' is not find.\n", str);
	else if (err == LAB_EXISTS)
		ft_printf("Label '%s' exists already\n", str);
	else if (err == TOO_MUCH_ARG_ERR)
		ft_printf("Too much arguments at [%d:%d] : '%s'.\n", line, column, str);
	else
		asm_error4(err, str, env);
}

void	asm_error4(int err, char *str, t_asm_env *env)
{
	int line;

	if (env)
		line = env->line;
	if (err == NAME_SIZE_ERR)
	{
		ft_printf("Line %d, name size is too big. Must be < %d.\n",
		line, PROG_NAME_LENGTH);
	}
	else if (err == COM_SIZE_ERR)
	{
		ft_printf("Line %d, comment is size too big. Must be < %d.\n",
		line, COMMENT_LENGTH);
	}
	else if (err == NAME_EXISTS)
		ft_printf("Line %d, name is already defined.\n", line);
	else
		asm_error5(err, str, env);
}

void	asm_error5(int err, char *str, t_asm_env *env)
{
	int line;

	if (env)
		line = env->line;
	if (err == COM_SIZE_ERR)
	{
		ft_printf("Line %d, comment is size too big. Must be < %d.\n",
		line, COMMENT_LENGTH);
	}
	else if (err == NAME_EXISTS)
		ft_printf("Line %d, name is already defined.\n", line);
	else if (err == COM_EXISTS)
		ft_printf("Line %d, comments are already defined.\n", line);
	else if (err == COMMAND_ERR)
		ft_printf("Line %d, command '%s' not found.\n", line, str);
	else
		asm_error6(err, env);
}

void	asm_error6(int err, t_asm_env *env)
{
	int line;

	if (env)
		line = env->line;
	if (err == NO_NAME)
	{
		ft_printf("Line %d, Your champion needs a name before instructions\n",
		line);
	}
	else if (err == NO_COMMENT)
	{
		ft_printf("Line %d, Your champ needs a comment before instructions\n",
		line);
	}
	else if (err == NO_INSTRUCTIONS)
		ft_printf("You need, at least, one instruction !\n");
	else if (err == WRONG_FORM_COM)
		ft_printf("wrong format. Name and com need to begin and end by \"\n");
}
