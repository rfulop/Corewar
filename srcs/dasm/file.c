/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:53:48 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/07 01:37:07 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			print_instr(int fd, int c)
{
	char	*ins;
	int		size;

	if (c < 1 || c > 16)
		dasm_error(NO_COMP, NULL);
	ins = g_op_tab[c - 1].inst;
	size = ft_strlen(ins);
	write(fd, "\t", 1);
	write(fd, ins, ft_strlen(ins));
	write(fd, "\t", 1);
}

void			parse_cor(t_dasm_env *env)
{
	int		i;
	int		inst;

	i = SRC_BEGIN;
	while (i < env->size_file)
	{
		inst = env->file[i];
		print_instr(env->fd, inst);
		++i;
		if (!g_op_tab[inst - 1].need_ocp)
		{
			if (inst == 1)
				i += print_dir4(env->fd, env->file + i);
			else
				i += print_dir2(env->fd, env->file + i);
		}
		else
			i += print_args(env->fd, inst, env->file + i);
		write(env->fd, "\n", 1);
	}
}

unsigned char	*open_bin(t_dasm_env *env, int fd)
{
	unsigned char *ret;

	if (!(ret = malloc(MEM_SIZE + 1)))
		dasm_error(MALLOC_ERR, NULL);
	env->size_file = read(fd, ret, MEM_SIZE);
	if (env->size_file > MEM_SIZE)
		dasm_error(SIZE_ERROR, NULL);
	return (ret);
}

void			create_file_cor(t_dasm_env *env, char *str)
{
	int		fd;
	int		len;
	char	*tmp;
	char	*name;

	len = ft_strlen(str) - 4;
	if (!(tmp = ft_strndup(str, len)))
		dasm_error(MALLOC_ERR, NULL);
	if (!(name = ft_strnew(len + 2)))
		dasm_error(MALLOC_ERR, NULL);
	name = ft_strcpy(name, tmp);
	name = ft_strcat(name, ".s");
	if ((fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
		dasm_error(OPEN_ERROR, str);
	ft_memdel((void*)&tmp);
	ft_memdel((void*)&name);
	env->fd = fd;
}
