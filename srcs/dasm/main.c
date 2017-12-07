/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:53:48 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/07 02:41:51 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_bin_len(unsigned char *str)
{
	int		i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

void	print_head_bis(t_dasm_env *env, char *comments, int binsize)
{
	write(env->fd, ".comment \"", 10);
	write(env->fd, comments, binsize);
	write(env->fd, "\"\n\n", 3);
}

void	print_head(t_dasm_env *env)
{
	char	*name;
	char	*comments;
	int		binsize;

	binsize = ft_bin_len(env->file + MAGIC_NB);
	if (binsize <= 0 || binsize > PROG_NAME_LENGTH)
		dasm_error(NAME_SIZE_ERR, NULL);
	if (!(name = ft_strnew(binsize + 1)))
		dasm_error(MALLOC_ERR, NULL);
	name[binsize] = '\0';
	ft_memcpy(name, env->file + MAGIC_NB, binsize);
	write(env->fd, ".name \"", 7);
	write(env->fd, name, binsize);
	write(env->fd, "\"\n", 2);
	binsize = ft_bin_len(env->file + PROG_NAME + PROG_SIZE + MAGIC_NB);
	if (binsize > COMMENT_LENGTH)
		dasm_error(COM_SIZE_ERR, NULL);
	if (!(comments = ft_strnew(binsize + 1)))
		dasm_error(MALLOC_ERR, NULL);
	comments[binsize] = '\0';
	ft_memcpy(comments, env->file + (PROG_NAME + PROG_SIZE + MAGIC_NB),
	binsize);
	print_head_bis(env, comments, binsize);
	ft_memdel((void*)&name);
	ft_memdel((void*)&comments);
}

void	loop(t_dasm_env *env, char **argv, int arg, int fd)
{
	env->file = open_bin(env, fd);
	check_magic_nb(env);
	create_file_cor(env, argv[arg]);
	print_head(env);
	parse_cor(env);
	argv[arg][ft_strlen(argv[arg]) - 4] = '\0';
	ft_printf("Writting output file to %s.s\n", argv[arg]);
}

int		main(int argc, char **argv)
{
	int			fd;
	int			arg;
	int			len;
	char		*line;
	t_dasm_env	env;

	arg = 1;
	while (arg < argc)
	{
		if ((fd = open(argv[arg], O_RDONLY)) == -1)
			dasm_error(SOURCE_ERR, argv[arg]);
		line = NULL;
		len = ft_strlen(argv[arg]) - 1;
		if (len > 3 && argv[arg][len] == 'r' && argv[arg][len - 1] == 'o' &&
		argv[arg][len - 2] == 'c' && argv[arg][len - 3] == '.')
			loop(&env, argv, arg, fd);
		else
			dasm_error(WRONG_FILE, argv[arg]);
		ft_memdel((void*)&env.file);
		++arg;
	}
	return (0);
}
