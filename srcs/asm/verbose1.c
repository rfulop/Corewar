/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:12:44 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/07 13:45:30 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	verbose_arg(t_asm_env *env, char *line, int arg, int hex)
{
	char	*t;
	char	*tmp2;

	verbose_arg_bis(line, arg);
	if (!(tmp2 = ft_itoa(hex)))
		asm_error(MALLOC_ERR, NULL, 0, 0);
	if (!(t = ft_conv_hex(tmp2, HEX2)))
		asm_error(MALLOC_ERR, NULL, 0, 0);
	if (arg == T_REG && hex == 16)
		env->verbose_line = ft_strcat(env->verbose_line, "10");
	else if ((line[0] != '-' && (ft_strlen(t) % 2)) || arg == T_REG)
	{
		env->verbose_line = ft_strcat(env->verbose_line, "0");
		if (arg == T_DIR4)
			env->verbose_line = ft_strncat(env->verbose_line, ft_strrev(t), 8);
		else
			env->verbose_line = ft_strncat(env->verbose_line, ft_strrev(t), 4);
	}
	else if (arg == T_DIR4)
		env->verbose_line = ft_strncat(env->verbose_line, swap_hex(t), 8);
	else
		env->verbose_line = ft_strncat(env->verbose_line, swap_hex(t), 4);
	env->verbose_line = ft_strcat(env->verbose_line, " ");
	ft_memdel((void*)&t);
}

void	verbose_inst(t_asm_env *env, char *ins, int hex)
{
	char *tmp;
	char *tmp2;

	ft_printf("Instruction:|");
	COLOR(C_CYAN);
	ft_printf("%s", ins);
	COLOR(C_RESET);
	ft_printf("| ");
	if (!(env->verbose_line = ft_strnew(30)))
		asm_error(MALLOC_ERR, NULL, 0, 0);
	if (!(tmp2 = ft_itoa(hex + 1)))
		asm_error(MALLOC_ERR, NULL, 0, 0);
	if (!(tmp = ft_convert_base(tmp2, DEC, HEX2)))
		asm_error(MALLOC_ERR, NULL, 0, 0);
	env->verbose_line = ft_strcat(env->verbose_line, tmp);
	ft_memdel((void*)&tmp);
	ft_memdel((void*)&tmp2);
	env->verbose_line = ft_strcat(env->verbose_line, " ");
}

void	verbose_dist_lab(int dist)
{
	ft_printf("(Jump dist: %d) ", dist);
}

void	verbose_lab(char *lab)
{
	ft_printf("label:|");
	COLOR(C_RED);
	write(1, lab, ft_strlen(lab) - 1);
	COLOR(C_RESET);
	ft_printf("| ");
}

void	verbose_ocp(t_asm_env *env, char ocp)
{
	char *tmp;
	char *tmp2;

	if (ocp)
	{
		ft_printf("Ocp: %hb (%#hhx) ", ocp, ocp);
		if (!(tmp2 = ft_itoa((unsigned char)ocp)))
			asm_error(MALLOC_ERR, NULL, 0, 0);
		tmp = ft_convert_base(tmp2, DEC, HEX2);
		env->verbose_line = ft_strcat(env->verbose_line, tmp);
		ft_memdel((void*)&tmp);
		ft_memdel((void*)&tmp2);
		env->verbose_line = ft_strcat(env->verbose_line, " ");
	}
	else
		ft_printf("No ocp ");
}
