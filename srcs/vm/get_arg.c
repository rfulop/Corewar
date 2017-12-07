/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 14:56:52 by lchety            #+#    #+#             */
/*   Updated: 2017/12/04 15:13:16 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				get_dir(t_vm *vm, t_proc *proc, int num, int pos)
{
	unsigned int	value;

	value = 0x0;
	value = (unsigned char)vm->ram[(pos + 1) % MEM_SIZE].mem;
	value = value << 8;
	value = value | (unsigned char)vm->ram[(pos + 2) % MEM_SIZE].mem;
	if (g_op_tab[proc->op.code - 1].direct_size)
	{
		if ((value & 0x8000) == 0x8000)
			value = (value - USHRT_MAX) - 1;
		proc->op.ar[num] = value;
		return ;
	}
	value = value << 8;
	value = value | (unsigned char)vm->ram[(pos + 3) % MEM_SIZE].mem;
	value = value << 8;
	value = value | (unsigned char)vm->ram[(pos + 4) % MEM_SIZE].mem;
	proc->op.ar[num] = value;
}

void				get_reg(t_vm *vm, t_proc *proc, int num, int pos)
{
	unsigned char	value;

	value = (unsigned char)vm->ram[(pos + REG_SIZE) % MEM_SIZE].mem;
	proc->op.ar[num] = value;
}

void				get_ind(t_vm *vm, t_proc *proc, int num, int pos)
{
	unsigned int	value;

	value = 0;
	value = value | (unsigned char)vm->ram[(pos + 1) % MEM_SIZE].mem;
	value = value << 8;
	value = value | (unsigned char)vm->ram[(pos + 2) % MEM_SIZE].mem;
	proc->op.ar[num] = value;
	if ((value & 0x8000) == 0x8000)
		proc->op.ar[num] = (value - USHRT_MAX) - 1;
}

int					get_indirect(t_vm *vm, t_op *op, int nb_arg)
{
	int	value;
	int	pos;

	value = 0x0;
	pos = op->pos_opcode + (op->ar[nb_arg] % IDX_MOD);
	value |= (unsigned char)vm->ram[modulo(pos, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(pos + 1, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(pos + 2, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(pos + 3, MEM_SIZE)].mem;
	return (value);
}
