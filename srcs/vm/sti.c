/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 20:54:19 by lchety            #+#    #+#             */
/*   Updated: 2017/12/04 15:46:55 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	sti_verbose(t_proc *proc, int addr)
{
	show_operations(proc);
	ft_printf("\n       | -> store to %d + %d = %d (with pc and mod %d)\n",
	proc->op.ar[1], proc->op.ar[2], proc->op.ar[1] + proc->op.ar[2], addr);
}

int		sti_set_value(t_vm *vm, t_proc *proc, int reg)
{
	int addr;

	addr = (proc->op.ar[1] + proc->op.ar[2]) % IDX_MOD;
	addr = proc->op.pos_opcode + addr;
	vm->ram[modulo(addr, MEM_SIZE)].mem = proc->reg[reg] >> 24;
	vm->ram[modulo(addr, MEM_SIZE)].num = proc->num;
	vm->ram[modulo(addr, MEM_SIZE)].blingbling = BLING_DELAY;
	vm->ram[modulo(addr + 1, MEM_SIZE)].mem = proc->reg[reg] >> 16;
	vm->ram[modulo(addr + 1, MEM_SIZE)].num = proc->num;
	vm->ram[modulo(addr + 1, MEM_SIZE)].blingbling = BLING_DELAY;
	vm->ram[modulo(addr + 2, MEM_SIZE)].mem = proc->reg[reg] >> 8;
	vm->ram[modulo(addr + 2, MEM_SIZE)].num = proc->num;
	vm->ram[modulo(addr + 2, MEM_SIZE)].blingbling = BLING_DELAY;
	vm->ram[modulo(addr + 3, MEM_SIZE)].mem = proc->reg[reg];
	vm->ram[modulo(addr + 3, MEM_SIZE)].num = proc->num;
	vm->ram[modulo(addr + 3, MEM_SIZE)].blingbling = BLING_DELAY;
	return (addr);
}

void	sti(t_vm *vm, t_proc *proc)
{
	int addr;
	int reg;

	if (!check_params(&proc->op))
		return ;
	reg = proc->op.ar[0];
	if (proc->op.ar_typ[1] == REG_CODE)
	{
		proc->op.ar[1] = proc->reg[proc->op.ar[1]];
		proc->op.ar_typ[1] = DIR_CODE;
	}
	else if (proc->op.ar_typ[1] == IND_CODE)
		proc->op.ar[1] = get_indirect(vm, &proc->op, 1);
	if (proc->op.ar_typ[2] == REG_CODE)
	{
		proc->op.ar[2] = proc->reg[proc->op.ar[2]];
		proc->op.ar_typ[2] = DIR_CODE;
	}
	addr = sti_set_value(vm, proc, reg);
	if (0x4 & vm->verbosity)
		sti_verbose(proc, addr);
}
