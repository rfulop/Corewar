/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:09:42 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/04 17:32:22 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_op(char *instr, t_asm_env *env, int col)
{
	int i;
	int ret;

	i = 0;
	ret = -1;
	while (i < 16)
	{
		if (!(ft_strcmp(instr, g_op_tab[i].inst)))
		{
			ret = i;
			break ;
		}
		++i;
	}
	if (ret == -1)
		asm_error(INST_ERROR, instr, env, col);
	return (ret);
}

void	check_parse_arg(char *str, int instr, t_asm_env *env, int col)
{
	if (instr == 1 || instr == 9 || instr == 12 || instr == 15)
		check_instr_1_9_12_15(str, env, col);
	else if (instr == 2 || instr == 13)
		check_instr_2_13(str, env, col);
	else if (instr == 3)
		check_instr_3(str, env, col);
	else if (instr == 4 || instr == 5)
		check_instr_4_5(str, env, col);
	else if (instr == 6 || instr == 7 || instr == 8)
		check_instr_6_7_8(str, env, col);
	else if (instr == 10)
		check_instr_10(str, env, col);
	else if (instr == 11)
		check_instr_11(str, env, col);
	else if (instr == 14)
		check_instr_14(str, env, col);
	else if (instr == 16)
		check_instr_16(str, env, col);
}

void	init_check_ins(t_check_ins *ch)
{
	ch->args = 0;
	ch->inst = -1;
	ch->label = 0;
	ch->word = NULL;
}

void	check_instr(char *line, t_asm_env *env)
{
	int			i;
	t_check_ins	ch;

	i = 0;
	init_check_ins(&ch);
	while (line[i] && !(char_is_com(line[i])))
	{
		i += until_is_not_space(line + i);
		ch.word = take_word(line + i);
		if (!ch.label && ch.inst == -1 && is_label_str(ch.word))
			++ch.label;
		else if (ch.inst == -1 && !char_is_com(ch.word[0]) && ch.word[0])
			ch.inst = check_op(ch.word, env, i);
		else
		{
			check_parse_arg(line + i, ch.inst + 1, env, i);
			ft_memdel((void*)&ch.word);
			++ch.args;
			break ;
		}
		i += ft_strlen(ch.word);
		ft_memdel((void*)&ch.word);
	}
	if (ch.inst != -1 && !ch.args)
		asm_error(NO_ARGUMENTS, line, env, i);
}

void	check_line(t_asm_env *env, char *line)
{
	int i;

	i = 0;
	if (!line)
		return ;
	i += until_is_not_space(line + i);
	if (line[i] == '.')
		check_header(env, line + i);
	else
	{
		i += until_is_not_space(line + i);
		if (char_is_com(line[i]) || !line[i])
			return ;
		if (env->name && env->comment)
			check_instr(line, env);
		else
		{
			if (!env->name)
				asm_error(NO_NAME, NULL, env, 0);
			else
				asm_error(NO_COMMENT, NULL, env, 0);
		}
	}
}
