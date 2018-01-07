/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:12:39 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/07 00:59:08 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	write_reg(t_asm_env *env, char *line)
{
	int		a;
	char	reg;
	char	*str;

	a = 0;
	line++;
	while (line[a] && ft_isdigit(line[a]))
		++a;
	if (!(str = ft_strndup(line, a)))
		asm_error(MALLOC_ERR, NULL, 0, 0);
	reg = ft_atoi(str);
	if (env->verbose)
		verbose_arg(env, line, T_REG, reg);
	ft_putchar_fd(reg, env->fd);
	ft_memdel((void*)&str);
}

void	write_dir_short(t_asm_env *env, char *line, int nb, int a)
{
	char	*label;
	short	dir2o;

	if (line[a] == LABEL_CHAR)
	{
		label = take_word(line + 1);
		dir2o = dist_label(env, label);
		ft_memdel((void*)&label);
	}
	else
		dir2o = nb;
	dir2o = reverse_short(dir2o);
	if (env->verbose)
		verbose_arg(env, line, T_DIR, dir2o);
	write(env->fd, &dir2o, 2);
}

void	write_dir_int(t_asm_env *env, char *line, int nb, int a)
{
	int		dir4o;
	char	*label;

	if (line[a] == LABEL_CHAR)
	{
		label = take_word(line + 1);
		dir4o = dist_label(env, label);
		ft_memdel((void*)&label);
	}
	else
		dir4o = nb;
	dir4o = reverse_int(dir4o);
	if (env->verbose)
		verbose_arg(env, line, T_DIR4, dir4o);
	write(env->fd, &dir4o, 4);
}

void	write_dir(t_asm_env *env, char *line, int i)
{
	int		a;
	int		nb;

	a = 0;
	++line;
	nb = ft_atoi(line);
	if (line[a] != LABEL_CHAR)
	{
		while (line[a] && ft_isdigit(line[a]))
			++a;
	}
	if (is_dir_int(i))
		write_dir_int(env, line, nb, a);
	else
		write_dir_short(env, line, nb, a);
}

void	write_ind(t_asm_env *env, char *line)
{
	int		a;
	short	ind;
	char	*str;

	a = 0;
	if (ft_isdigit(*line) || *line == '-')
	{
		while (line[a] && (line[a] == '-' || ft_isdigit(line[a])))
			++a;
		if (!(str = ft_strndup(line, a)))
			asm_error(MALLOC_ERR, NULL, 0, 0);
		ind = ft_atoi(str);
	}
	else
	{
		str = take_word(line + 1);
		ind = dist_label(env, str);
	}
	ft_memdel((void*)&str);
	ind = reverse_short(ind);
	if (ft_isdigit(*line) && env->verbose)
		verbose_arg(env, line, T_IND, ind);
	else if (env->verbose)
		verbose_arg(env, line, T_LAB, ind);
	write(env->fd, &ind, 2);
}
