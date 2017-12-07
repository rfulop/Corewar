/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:13:29 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/01 17:38:36 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	write_comment(t_asm_env *env, char *line)
{
	int a;
	int tmp;
	int c;
	int size;

	a = 0;
	c = 0;
	tmp = 0;
	size = reverse_int(env->size);
	write(env->fd, &size, 4);
	while (line[a] != '\"')
		++a;
	a++;
	tmp = a;
	a = 0;
	while (line[tmp + a] != '\"')
	{
		ft_putchar_fd(line[tmp + a], env->fd);
		++a;
	}
	while (a != PROG_COMS)
	{
		ft_putchar_fd(c, env->fd);
		a++;
	}
}

void	write_name(t_asm_env *env, char *line)
{
	int a;
	int tmp;
	int c;
	int magic;

	tmp = 0;
	c = 0;
	magic = reverse_int(COREWAR_EXEC_MAGIC);
	write(env->fd, &magic, 4);
	a = 4;
	while (line[a] != '\"')
		++a;
	++a;
	tmp = a;
	a = 0;
	while (line[tmp + a] != '\"')
	{
		ft_putchar_fd(line[tmp + a], env->fd);
		++a;
	}
	while (a != PROG_NAME)
	{
		ft_putchar_fd(c, env->fd);
		a++;
	}
}

void	write_header(t_asm_env *env, char *line, int printmode)
{
	int i;

	i = until_is_not_space(line);
	if (!printmode)
		;
	else
	{
		if (line[i + 1] == 'n' && line[i + 2] == 'a' && line[i + 3] == 'm' &&
				line[i + 4] == 'e')
			write_name(env, line + i);
		else
			write_comment(env, line + i);
	}
}
