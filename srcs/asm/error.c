/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:09:42 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/04 21:58:55 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	display_error(int err)
{
	if (err >= ERROR_MIN && err <= ERROR_MAX)
	{
		COLOR(C_RED);
		ft_printf("Error: ");
		COLOR(C_RESET);
	}
}

void	display_current_line(t_asm_env *env, int err, int column)
{
	int i;

	if (!env || !env->current_line)
		exit(EXIT_FAILURE);
	if (err == TOO_MUCH_ARG_ERR || err == LEX_ERROR)
		--column;
	if (err >= ERROR_MIN && err <= ERROR_MAX)
	{
		i = 0;
		ft_printf("%s\n", env->current_line);
		while (i < column)
		{
			if (env->current_line[i] == TAB)
				write(1, "\t", 1);
			else
				write(1, " ", 1);
			++i;
		}
		COLOR(C_GREEN);
		ft_printf("^\n");
		COLOR(C_RESET);
	}
}

void	put_line_col(int err, int line, int column)
{
	if (err == INST_ERROR || err == LEX_ERROR || err == BAD_ARG_DIR ||
	err == BAD_ARG_REG || err == BAD_ARG_IND || err == BAD_ARG_REG_DIR ||
	err == BAD_ARG_REG_IND || err == BAD_ARG_IND_DIR || err == NO_ARGUMENTS ||
	err == BAD_ARG_REG_DIR_IND || err == WRONG_FORM_COM)
		ft_printf("At [%d:%d], ", line, column);
}

void	asm_error(int err, char *str, t_asm_env *env, int column)
{
	int line;

	if (env && env->debug && env->ko)
		return ;
	display_error(err);
	if (err == NO_FILE_ERR || err == SOURCE_ERR || err == FILE_ERROR ||
	err == SIZE_MAX_ERR)
		asm_error1(err, str, env);
	else if (env)
		line = env->line;
	free_labels(env);
	if (env && env->ko)
		return ;
	if (env && env->debug)
		++env->ko;
	put_line_col(err, line, column);
	asm_error2(err, str, env, column);
	display_current_line(env, err, column);
	if (!env->debug)
		exit(EXIT_FAILURE);
}

void	asm_error1(int err, char *str, t_asm_env *env)
{
	if (err == NO_FILE_ERR)
		ft_printf("Missing filename.\n");
	else if (err == SOURCE_ERR)
		ft_printf("Can't read source file '%s'.\n", str);
	else if (err == FILE_ERROR)
		ft_printf("'%s' is not a .s file.\n", str);
	else if (err == SIZE_MAX_ERR)
	{
		ft_printf("File '%s' as too large a code (%d bytes > %d bytes)\n",
		str, env->size, CHAMP_MAX_SIZE);
	}
	exit(EXIT_FAILURE);
}
