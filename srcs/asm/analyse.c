/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:12:39 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/01 16:13:53 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_ocp(t_asm_env *env, int i, char *line)
{
	int		a;
	int		res;
	char	*ocp;

	a = 0;
	res = 0;
	ocp = NULL;
	ft_putchar_fd(i + 1, env->fd);
	line = moove_on_line(line);
	while (line[a] && !(char_is_com(line[a])))
	{
		res = detect_arg(line + a);
		ocp = concat_opcode(ocp, res);
		a += goto_nextarg(line + a);
	}
	write_ocp(env, ocp);
	write_args(env, line, i + 1);
	ft_memdel((void*)&ocp);
}

void	op_no_ocp(t_asm_env *env, int i, char *line)
{
	int		a;
	int		res;

	if (env->verbose && env->print)
		verbose_ocp(env, 0);
	a = 0;
	res = 0;
	ft_putchar_fd(i + 1, env->fd);
	line = moove_on_line(line);
	while (line[a] && !(char_is_com(line[a])))
	{
		res = detect_arg(line + a);
		a += goto_nextarg(line + a);
	}
	write_args(env, line, i + 1);
}

int		analyse_args(int oct, char *line, int i)
{
	if (*line == REG_CHAR)
		oct += REG_SIZE;
	else if (*line == DIRECT_CHAR)
	{
		if (is_dir_int(i + 1))
			oct += DIR_SIZE;
		else
			oct += IND_SIZE;
	}
	else if (*line == LABEL_CHAR || ft_isdigit(*line))
		oct += IND_SIZE;
	else if (*line == '-' && ft_isdigit(line[1]))
		oct += IND_SIZE;
	return (oct);
}

int		analyse(int oct, char *line, int i)
{
	int	a;

	a = 0;
	while (line[a] && line[a] != '\n')
	{
		while (line[a] == LABEL_CHAR)
			++a;
		while (line[a] && (line[a] == '-' || is_label_char(line[a])))
			++a;
		while (line[a] && is_space(line[a]))
			++a;
		if (line[a] == SEPARATOR_CHAR)
			++a;
		oct = analyse_args(oct, line + a, i);
		if (line[a] == SEPARATOR_CHAR)
			a++;
		if (line[a] == DIRECT_CHAR)
			a++;
		if (char_is_com(line[a]))
			return (oct);
	}
	return (oct);
}
