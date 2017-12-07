/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 20:55:40 by lchety            #+#    #+#             */
/*   Updated: 2017/12/01 15:13:32 by amacieje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		proc_reg(t_vm *vm, t_proc *proc, int reg_nb)
{
	int		addr;

	addr = 0;
	addr = proc->op.ar[0] % IDX_MOD;
	proc->reg[reg_nb] = 0;
	proc->reg[reg_nb] = (unsigned char)vm->ram[modulo(proc->op.pos_opcode
		+ addr, MEM_SIZE)].mem;
	proc->reg[reg_nb] <<= 8;
	proc->reg[reg_nb] |= (unsigned char)vm->ram[modulo(proc->op.pos_opcode
		+ addr + 1, MEM_SIZE)].mem;
	proc->reg[reg_nb] <<= 8;
	proc->reg[reg_nb] |= (unsigned char)vm->ram[modulo(proc->op.pos_opcode
		+ addr + 2, MEM_SIZE)].mem;
	proc->reg[reg_nb] <<= 8;
	proc->reg[reg_nb] |= (unsigned char)vm->ram[modulo(proc->op.pos_opcode
		+ addr + 3, MEM_SIZE)].mem;
}

void		ld(t_vm *vm, t_proc *proc)
{
	int		reg_nb;

	reg_nb = proc->op.ar[1];
	if (!check_params(&proc->op))
		return ;
	if (proc->op.ar_typ[0] == IND_CODE)
		proc_reg(vm, proc, reg_nb);
	else
		proc->reg[reg_nb] = proc->op.ar[0];
	proc->carry = (proc->reg[reg_nb] == 0) ? 1 : 0;
	proc->op.ar[0] = proc->reg[reg_nb];
	if (0x4 & vm->verbosity)
	{
		show_operations(proc);
		ft_printf("\n");
	}
}
