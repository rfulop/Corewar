/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 22:10:50 by lchety            #+#    #+#             */
/*   Updated: 2017/12/07 16:44:37 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			usage(void)
{
	ft_printf("Usage: ./corewar [-d N -v N | -ncurses ] <[-n N] ");
	ft_printf("champion1.cor> <...>\n");
	ft_printf("  -d N\t\t: Dumps memory after N cycles then exits\n");
	ft_printf("  -v N\t\t: Verbosity levels, can be added together to enable ");
	ft_printf("several\n");
	ft_printf("\t\t\t- 0 : Show only essentials\n");
	ft_printf("\t\t\t- 1 : Show lives\n");
	ft_printf("\t\t\t- 2 : Show cycles\n");
	ft_printf("\t\t\t- 4 : Show operations (Params are NOT litteral ...)\n");
	ft_printf("\t\t\t- 8 : Show deaths\n");
	ft_printf("\t\t\t- 16 : Show PC movements (Except for jumps)\n");
	ft_printf("  -ncurses\t: Ncurses output mode\n");
	ft_printf("  -n N\t\t: Champion number (position at initalisation of ");
	ft_printf("memory)\n");
	exit(EXIT_FAILURE);
}

void			animate_proc(t_vm *vm, t_proc *proc)
{
	vm->ram[proc->pc % MEM_SIZE].pc = 0;
	if (!proc->op.active)
	{
		if (is_opcode(vm->ram[proc->pc % MEM_SIZE].mem))
			create_op(proc, vm->ram[proc->pc % MEM_SIZE].mem);
		else
			proc->pc = (proc->pc + 1) % MEM_SIZE;
	}
	else
	{
		proc->op.loadtime--;
		if (proc->op.loadtime <= 0)
		{
			if (fill_cur_op(vm, proc))
				g_op_tab[proc->op.code - 1].func(vm, proc);
			if (proc->op.code != 9 ||
				(proc->op.code == 9 && !proc->carry))
				proc->pc += move_pc(proc);
			if (16 & vm->verbosity)
				show_pc_move(vm, proc);
			delete_op(proc);
		}
	}
	vm->ram[proc->pc % MEM_SIZE].pc = proc->num;
}

int				count_proc(t_vm *vm)
{
	int				i;
	t_proc			*proc;

	i = 0;
	proc = vm->proc;
	while (proc)
	{
		if (proc->active)
			i++;
		proc = proc->next;
	}
	return (i);
}

void			run(t_vm *vm)
{
	t_proc			*proc;

	while (process_living(vm))
	{
		if (!((vm->cycle + 1) % vm->ctd))
			reset_live(vm);
		if (2 & vm->verbosity)
			ft_printf("It is now cycle %d\n", vm->cycle + 1);
		call_ncurses(vm);
		proc = vm->proc;
		while (proc != NULL)
		{
			if (proc->active)
				animate_proc(vm, proc);
			proc->last_pc = proc->pc;
			proc = proc->next;
		}
		vm->cycle++;
		if (vm->dump != -1 && !vm->ncurses)
			dump(vm);
	}
	if (vm->last_one)
		ft_printf("Last_one => %s\n", vm->last_one->file_name);
}

int				main(int argc, char **argv)
{
	t_vm			vm;
	T_WINDOW		*w;

	init_vm(&vm);
	if (check_arg(&vm, argc, argv))
		error("Error\n");
	create_players(&vm);
	if (vm.ncurses)
		init_ncurses(&w);
	run(&vm);
	get_winner(&vm);
	if (vm.ncurses)
	{
		vm.pause = 1;
		call_ncurses(&vm);
	}
	if (vm.ncurses)
		endwin();
	ft_printf("Contestant %d, \"%s\", has won !\n", vm.winner,
		vm.player[vm.winner].name);
	free_everything(&vm);
	return (0);
}
