/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:12:39 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/04 22:02:51 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_env(t_asm_env *env)
{
	env->name = 0;
	env->comment = 0;
	env->bytes = 1;
	env->line = 1;
	env->ko = 0;
	env->current_line = NULL;
	env->verbose_line = NULL;
}

void	print_mode_verbose(t_asm_env *env)
{
	COLOR(C_GREEN);
	ft_printf("Total bytes: ");
	COLOR(C_RESET);
	ft_printf("%d\n\n", env->bytes - 1);
}

void	print_help(void)
{
	ft_printf("Usage : ./asm [-[+]hvd] {*.cor}\n");
	ft_printf("Options : \n");
	ft_printf("h : Print help\n");
	ft_printf("v : Verbose Mode\n");
	ft_printf("d : Debug Mode\n");
}

void	loop_args(t_asm_env *env, char **argv, int arg)
{
	int fd;

	if ((fd = open(argv[arg], O_RDONLY)) == -1)
		asm_error(SOURCE_ERR, argv[arg], 0, 0);
	if (!check_name(argv[arg]))
		asm_error(FILE_ERROR, argv[arg], 0, 0);
	check_mode(env, argv[arg], fd);
	create_file(env, argv[arg]);
	print_mode(env, argv[arg]);
	argv[arg][ft_strlen(argv[arg]) - 2] = '\0';
	ft_printf("Writting output program to %s.cor\n", argv[arg]);
	free_labels(env);
}

int		main(int argc, char **argv)
{
	int			arg;
	t_asm_env	env;

	if (argc == 1)
	{
		print_help();
		asm_error(NO_FILE_ERR, NULL, 0, 0);
	}
	env.debug = 0;
	env.verbose = 0;
	arg = parse_args(&env, argv);
	if (env.debug)
		debug_mode(&env, 0);
	if (argc == arg)
		asm_error(NO_FILE_ERR, NULL, 0, 0);
	while (arg < argc)
	{
		loop_args(&env, argv, arg);
		++arg;
	}
	return (0);
}
