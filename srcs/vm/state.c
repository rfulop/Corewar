/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 14:41:41 by lchety            #+#    #+#             */
/*   Updated: 2017/10/16 17:26:34 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// void	idle_state(t_vm *vm, t_proc *proc)
// {
// 	// printf("IDLE %d\n", vm->cycle);
//
// 	// printf("------------IDLE_STATE------------\n");
// 	// printf("SEGV_1\n");
// 	// printf("proc->pc = %d\n", proc->pc);
//
// 	if ((proc->op = create_op(vm, proc, vm->ram[proc->pc % MEM_SIZE].mem)))
// 	{
// 		// printf("proc num : %d   delay : %d\n", proc->id, proc->op->loadtime);
// 		proc->state = WAIT;
// 	}
// 	else
// 		proc->pc = (proc->pc + 1) % MEM_SIZE;
//
// }

void	idle_state(t_vm *vm, t_proc *proc)
{
	// printf("------------WAIT_STATE------------\n");
	if(!proc->op)
	{
		if (is_opcode(vm->ram[proc->pc % MEM_SIZE].mem))
		{
			proc->op = create_op(vm, proc, vm->ram[proc->pc % MEM_SIZE].mem);
		}
		else
		{
			proc->pc = (proc->pc + 1) % MEM_SIZE;
		}
	}
	else
	{
		proc->op->loadtime--;
		if (proc->op->loadtime <= 0)
		{
			fill_cur_op(vm, proc);
			if (op_tab[proc->op->code - 1].func != NULL)
				op_tab[proc->op->code - 1].func(vm, proc);
			proc->op = NULL;
		}
	}
}
//
// void	wait_state(t_vm *vm, t_proc *proc)
// {
// 	printf("------------WAIT_STATE------------\n");
// 	proc->op->loadtime--;
//
// 	if (proc->op->loadtime <= 0)
// 	{
// 		fill_cur_op(vm, proc);
// 		if (op_tab[proc->op->code - 1].func != NULL)
// 		{
// 			// printf()
// 			show_operations(vm, proc);
// 			op_tab[proc->op->code - 1].func(vm, proc);
// 		}
// 		proc->state = IDLE;
// 	}
// }
