/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:03:11 by lchety            #+#    #+#             */
/*   Updated: 2017/12/04 14:58:26 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	live(t_vm *vm, t_proc *proc)
{
	int		num;

	vm->lives_in_cycle++;
	proc->last_live = vm->cycle + 1;
	num = 0;
	num = proc->op.ar[0] * -1;
	if (4 & vm->verbosity)
	{
		show_operations(proc);
		ft_printf("\n");
	}
	if (num >= 1 && num <= vm->nb_player)
	{
		vm->player[num].life_signal++;
		vm->player[num].last_live = vm->cycle;
		vm->ram[modulo(proc->op.pos_opcode, MEM_SIZE)].live = BLING_LIVE;
		if (5 & vm->verbosity)
		{
			ft_printf("Player %d (%s) is said to be alive\n",
			num, vm->player[num].name);
		}
	}
}
