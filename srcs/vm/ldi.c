/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlambert <mlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 00:20:16 by mlambert          #+#    #+#             */
/*   Updated: 2017/12/04 14:54:33 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	ldi_get_addr(t_proc *proc)
{
	unsigned int addr;

	addr = (proc->op.ar[0] + proc->op.ar[1]) % IDX_MOD;
	addr = addr + proc->op.pos_opcode;
	return (addr);
}

unsigned int	ldi_get_value(t_vm *vm, unsigned int addr)
{
	unsigned int value;

	value = 0x0;
	value |= (unsigned char)vm->ram[modulo(addr, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(addr + 1, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(addr + 2, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(addr + 3, MEM_SIZE)].mem;
	return (value);
}

void			ldi(t_vm *vm, t_proc *proc)
{
	unsigned int addr;

	if (!check_params(&proc->op))
		return ;
	if (proc->op.ar_typ[0] == REG_CODE)
	{
		proc->op.ar[0] = proc->reg[proc->op.ar[0]];
		proc->op.ar_typ[0] = DIR_CODE;
	}
	if (proc->op.ar_typ[1] == REG_CODE)
	{
		proc->op.ar[1] = proc->reg[proc->op.ar[1]];
		proc->op.ar_typ[1] = DIR_CODE;
	}
	if (proc->op.ar_typ[2] == REG_CODE && !check_reg(proc->op.ar[2]))
		return ;
	addr = ldi_get_addr(proc);
	proc->reg[proc->op.ar[2]] = ldi_get_value(vm, addr);
	if (0x4 & vm->verbosity)
	{
		show_operations(proc);
		ft_printf("\n| -> load from %d + %d = %d (with pc and mod %d)",
		proc->op.ar[0], proc->op.ar[1], proc->op.ar[0] + proc->op.ar[1], addr);
		ft_printf("\n");
	}
}
