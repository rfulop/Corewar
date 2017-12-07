/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:12:39 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/04 18:36:22 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		find_op_no_ocp(t_asm_env *env, char *line, int i)
{
	if (env->print == PRINT_MODE)
		op_no_ocp(env, i, line);
	return (i);
}

int		find_op_ocp(t_asm_env *env, char *line, int i)
{
	if (env->print == PRINT_MODE)
		op_ocp(env, i, line);
	return (i);
}

int		find_op(t_asm_env *env, char *word, char *line)
{
	int	i;
	int	tmp;
	int	oct;

	oct = 1;
	i = 0;
	tmp = 0;
	while (g_op_tab[i].inst)
	{
		if (!ft_strcmp(word, g_op_tab[i].inst))
		{
			if (env->verbose && env->print == PRINT_MODE)
				verbose_inst(env, word, i);
			if (!g_op_tab[i].need_ocp)
				tmp = find_op_no_ocp(env, line, i);
			else
			{
				tmp = find_op_ocp(env, line, i);
				++oct;
			}
			oct = analyse(oct, line, tmp);
		}
		++i;
	}
	return (oct == 1 ? 0 : oct);
}
