/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:03:11 by lchety            #+#    #+#             */
/*   Updated: 2017/10/16 18:35:45 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	live(t_vm *vm, t_proc *proc)
{
	if (!vm->ncurses && vm->debug)
		printf(">>>>>ENTER_LIVE<<<<< : Cycle > %d\n", vm->cycle);
	int		num;

	num = 0;
	// printf("NUM player => %d\n", proc->op->ar[0]);

	if (!vm->ncurses && vm->debug)
	{
		printf("opcode pos : %d\n", proc->op->pos_opcode);
		printf("fuck num %d\n", (int)proc->op->ar[0]);
		printf("fuck num %x\n", (int)proc->op->ar[0]);
	}
	num = proc->op->ar[0] * -1;

	// printf("fuck num %d\n", num);

	if (num >= 1 && num <= vm->nb_player)
	{
		// printf("LIVE HERE ##################################\n");
		vm->player[num].life_signal++;
		proc->last_live = vm->cycle + 1;
		vm->ram[proc->op->pos_opcode].live = BLING_LIVE;
	}
	else
	{
		// printf("Live for Unknown Player... \n");
	}

	if (0x4 & vm->verbosity)
	{
		show_operations(vm, proc);
		printf("\n");
	}
}
