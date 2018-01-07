/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:42:53 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/07 15:49:49 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_mode(t_asm_env *env, char *name, int fd)
{
	char	*line;

	init_env(env);
	line = NULL;
	env->print = 0;
	env->labs = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		env->current_line = line;
		check_line(env, line);
		parse(env, line);
		ft_memdel((void*)&line);
		++env->line;
	}
	env->current_line = line;
	if (!env->name)
		asm_error(NO_NAME, NULL, env, 0);
	if (!env->comment)
		asm_error(NO_COMMENT, NULL, env, 0);
	if (env->bytes == 1)
		asm_error(NO_INSTRUCTIONS, NULL, env, 0);
	env->size = env->bytes - 1;
	if (env->size > CHAMP_MAX_SIZE)
		asm_error(SIZE_MAX_ERR, name, env, 0);
}

void	print_mode(t_asm_env *env, char *file)
{
	int		fd;
	char	*line;

	init_env(env);
	line = NULL;
	env->print = 1;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		parse(env, line);
		ft_memdel((void*)&line);
		if (env->verbose && env->verbose_line)
		{
			COLOR(C_GREEN);
			ft_printf("-> ");
			COLOR(C_RESET);
			ft_printf("0%s\n\n", env->verbose_line);
			ft_memdel((void*)&env->verbose_line);
		}
		++env->line;
	}
	if (env->verbose)
		print_mode_verbose(env);
}

void	debug_mode(t_asm_env *env, int fd)
{
	char	*line;

	init_env(env);
	line = NULL;
	env->fd = 0;
	env->print = 0;
	env->labs = NULL;
	ft_printf("********** DEBUG MODE **********\n");
	while (get_next_line(fd, &line) > 0)
	{
		env->current_line = line;
		env->ko = 0;
		check_line(env, line);
		if (!env->ko)
		{
			ft_printf("This instruction is ");
			COLOR(C_GREEN);
			ft_printf("OK.\n\n");
			COLOR(C_RESET);
		}
		ft_memdel((void*)&line);
		++env->line;
	}
}

void	check_args_letter(t_asm_env *env, char let)
{
	if (let == 'h')
		print_help();
	else if (let == 'v')
		env->verbose = 1;
	else if (let == 'd')
		env->debug = 1;
	else
	{
		ft_printf("Invalid argument\n");
		print_help();
		exit(EXIT_FAILURE);
	}
}

int		parse_args(t_asm_env *env, char **argv)
{
	int a;
	int b;

	a = 1;
	while (argv[a] && *argv[a] == '-')
	{
		b = 1;
		while (argv[a][b])
		{
			check_args_letter(env, argv[a][b]);
			++b;
		}
		if (b == 1)
		{
			ft_printf("Invalid argument\n");
			print_help();
			exit(EXIT_FAILURE);
		}
		++a;
	}
	return (a);
}
