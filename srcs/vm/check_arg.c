/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 11:49:01 by lchety            #+#    #+#             */
/*   Updated: 2017/12/05 14:45:36 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		ft_strargv(int argc, char **argv, char *str)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strstr(argv[i], str))
			return (i);
		i++;
	}
	return (0);
}

int		srch_nb_dump(int argc, char **argv)
{
	int ret;
	int nb;

	ret = 0;
	nb = 0;
	if ((ret = ft_strargv(argc, argv, "-d")))
	{
		if (ft_strlen(argv[ret]) > 2)
			error("Bad argument\n");
		if ((ret + 1) < argc && ft_str_isdigit(argv[ret + 1]))
			return (ft_atoi(argv[ret + 1]));
		else
			error("Dump bad number\n");
	}
	return (-1);
}

int		srch_verbose(int argc, char **argv)
{
	int ret;
	int nb;

	ret = 0;
	nb = 0;
	if ((ret = ft_strargv(argc, argv, "-v")))
	{
		if ((ret + 1) < argc && ft_str_isdigit(argv[ret + 1]))
			return (ft_atoi(argv[ret + 1]));
		else
			error("Verbosity bad number\n");
	}
	return (0);
}

int		srch_ncurses(int argc, char **argv)
{
	int ret;

	ret = 0;
	if ((ret = ft_strargv(argc, argv, "-ncurses")))
		return (1);
	return (0);
}

int		check_arg(t_vm *vm, int argc, char **argv)
{
	if (argc == 1)
		usage();
	vm->dump = srch_nb_dump(argc, argv);
	if (!vm->dump)
		++vm->dump;
	vm->ncurses = srch_ncurses(argc, argv);
	vm->verbosity = srch_verbose(argc, argv);
	if (srch_players(vm, argc, argv))
		return (1);
	return (0);
}
