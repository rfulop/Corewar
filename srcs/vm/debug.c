/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:13:38 by lchety            #+#    #+#             */
/*   Updated: 2017/10/17 02:04:33 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	show_mem(t_vm *vm)
{
	printf(">>>>>>>>SHOW MEM<<<<<<<<\n");
	printf("Cycle : %d\n", vm->cycle);
	int i;
	i = 0;

	while (i < MEM_SIZE)
	{
		printf("%02x ", (unsigned char)vm->ram[i].mem);
		if (i / 64 != (i + 1) / 64)
			printf("\n");
		i++;
	}
	printf("\n\n");
}

void	show_proc_nb(t_vm *vm)
{
	t_proc *tmp;
	int i;

	i = 0;
	tmp = vm->proc;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	// printf("NB_PROC => %d\n", i);
}

void	debug_display_proc(t_vm *vm)
{
	t_proc *tmp;
	int i;

	i = 0;
	tmp = vm->proc;
	while (tmp)
	{
		move (24 + i, 198);
		printw("Proc n:%d on:%d num:%d pc:%d live:%d", i, tmp->active, tmp->num, tmp->pc, tmp->last_live);
		tmp = tmp->next;
		i++;
	}


}

static void	display_args(t_vm *vm, t_proc *proc, int n)
{
	if (proc->op->ar_typ[n] == REG_CODE)
		printf("r");
	printf("%d", proc->op->ar[n]);
}

void	show_operations(t_vm *vm, t_proc *proc)
{
	int	nb_arg;
	int i;

	i = 0;
	nb_arg = op_tab[proc->op->code - 1].nb_arg;
	printf("P%5d | %s", proc->id + 1, op_tab[proc->op->code - 1].inst);
	while (i < nb_arg)
	{
		printf(" ");
		display_args(vm, proc, i);
		i++;
	}
}

void	show_pc_move(t_vm *vm, t_proc *proc)
{
	if (proc->pc - proc->last_pc)
		printf("ADV %d (%0#4x -> %0#4x)\n", proc->pc - proc->last_pc, proc->last_pc, proc->pc);

}
