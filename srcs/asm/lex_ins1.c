/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_ins1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:09:42 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/04 19:33:20 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_instr_endline(char *str, t_asm_env *env, int col)
{
	int i;

	i = until_is_not_space(str);
	if (!(char_is_com(str[i])) && str[i] != '\0')
		asm_error(TOO_MUCH_ARG_ERR, str, env, col + i);
}

void	check_instr_1_9_12_15(char *str, t_asm_env *env, int col)
{
	int i;
	int arg;

	i = until_is_not_space(str);
	arg = is_dir(str + i);
	if (!arg)
		asm_error(BAD_ARG_DIR, str + i, env, col + i);
	i += arg;
	check_instr_endline(str + i, env, col + i);
}

void	check_instr_2_13(char *str, t_asm_env *env, int col)
{
	int i;
	int arg;

	i = until_is_not_space(str);
	arg = is_ind_or_dir(str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg(str + i);
	if (!arg)
		asm_error(BAD_ARG_REG, str + i, env, col + i);
	i += arg;
	check_instr_endline(str + i, env, col + i);
}

void	check_instr_3(char *str, t_asm_env *env, int col)
{
	int i;
	int arg;

	i = until_is_not_space(str);
	arg = is_reg(str + i);
	if (!arg)
		asm_error(BAD_ARG_REG, str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg_or_ind(str + i, env, col + i);
	if (!arg)
		asm_error(BAD_ARG_REG_IND, str + i, env, col + i);
	i += arg;
	check_instr_endline(str + i, env, col + i);
}

void	check_instr_4_5(char *str, t_asm_env *env, int col)
{
	int i;
	int arg;

	i = until_is_not_space(str);
	arg = is_reg(str + i);
	if (!arg)
		asm_error(BAD_ARG_REG, str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg(str + i);
	if (!arg)
		asm_error(BAD_ARG_REG, str + i, env, col + i);
	i += arg;
	i += until_next_arg(str + i, env, col + i);
	arg = is_reg(str + i);
	if (!arg)
		asm_error(BAD_ARG_REG, str + i, env, col + i);
	i += arg;
	check_instr_endline(str + i, env, col + i);
}
