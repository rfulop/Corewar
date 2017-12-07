/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_ins2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:09:42 by rfulop            #+#    #+#             */
/*   Updated: 2017/11/04 19:15:35 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_instr_6_7_8(char *str, t_asm_env *env, int col)
{
	int i;
	int arg;

	i = until_is_not_space(str);
	arg = is_reg_or_ind_or_dir(str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg_or_ind_or_dir(str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg(str + i);
	if (!arg)
		asm_error(BAD_ARG_REG, str + i, env, col + i);
	i += arg;
	check_instr_endline(str + i, env, col + i);
}

void	check_instr_10(char *str, t_asm_env *env, int col)
{
	int i;
	int arg;

	i = until_is_not_space(str);
	arg = is_reg_or_ind_or_dir(str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg_or_dir(str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg(str + i);
	if (!arg)
		asm_error(BAD_ARG_REG, str + i, env, col + i);
	i += arg;
	check_instr_endline(str + i, env, col + i);
}

void	check_instr_11(char *str, t_asm_env *env, int col)
{
	int i;
	int arg;

	i = until_is_not_space(str);
	arg = is_reg(str + i);
	if (!arg)
		asm_error(BAD_ARG_REG, str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg_or_ind_or_dir(str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg_or_dir(str + i, env, col + i);
	i += arg;
	check_instr_endline(str + i, env, col + i);
}

void	check_instr_14(char *str, t_asm_env *env, int col)
{
	int i;
	int arg;

	i = until_is_not_space(str);
	arg = is_reg_or_ind_or_dir(str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg_or_dir(str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg(str + i);
	if (!arg)
		asm_error(BAD_ARG_REG, str + i, env, col + i);
	i += arg;
	check_instr_endline(str + i, env, col + i);
}

void	check_instr_16(char *str, t_asm_env *env, int col)
{
	int i;
	int arg;

	i = until_is_not_space(str);
	arg = is_reg(str + i);
	if (!arg)
		asm_error(BAD_ARG_REG, str + i, env, col + i);
	i += arg;
	check_instr_endline(str + i, env, col + i);
}
