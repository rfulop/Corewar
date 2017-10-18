/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlambert <mlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 00:20:16 by mlambert          #+#    #+#             */
/*   Updated: 2017/10/15 22:26:15 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// int		get_ind_in_ram()
// {
//
//
// }


static int	get_indirect(t_vm *vm, t_op *op, int nb_arg)
{
	int	value;
	int	pos;

	value = 0x0;
	pos = op->pos_opcode + (op->ar[nb_arg] % IDX_MOD);
	// printf("POS LDI %d\n", pos);
	value |= (unsigned char)vm->ram[modulo(pos, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(pos + 1, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(pos + 2, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(pos + 3, MEM_SIZE)].mem;

	return (value);
}

void		ldi(t_vm *vm, t_proc *proc)
{
	if (!vm->ncurses)
		printf(">>>>>>ENTER LDI<<<<<<\n");
	unsigned int		addr;
	unsigned int		reg_nb;
	int ar1;
	int ar2;
	int value;

	value = 0x0;
	addr = 0;

	if (proc->op->ar_typ[0] == REG_CODE)
	{
		// printf("reg %d\n", proc->op->ar[0]);
		proc->op->ar[0] = proc->reg[proc->op->ar[0]];
	}
	else if (proc->op->ar_typ[0] == IND_CODE)// IND CODE
	{
		proc->op->ar[0] = get_indirect(vm, proc->op, 0);
		printf("ar1 IND => %d\n", proc->op->ar[0]);
		// ar1 = vm->ram[].mem         proc->op->pos_opcode
	}

	if (proc->op->ar_typ[1] == REG_CODE)
	{
		// printf("reg %d\n", proc->op->ar[1]);
		proc->op->ar[1] = proc->reg[proc->op->ar[1]];
	}

	// printf("proc->op->ar[0] : %d\n", proc->op->ar[0]);
	// printf("proc->op->ar[0] : %d\n", proc->op->ar[1]);

	addr = (proc->op->ar[0] + proc->op->ar[1]) % IDX_MOD;
	printf("addr : %d\n", addr);
	addr = addr + proc->op->pos_opcode;
	printf("addr : %d\n", addr);

	value |= (unsigned char)vm->ram[modulo(addr, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(addr + 1, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(addr + 2, MEM_SIZE)].mem;
	value = value << 8;
	value |= (unsigned char)vm->ram[modulo(addr + 3, MEM_SIZE)].mem;
	printf("value : %x\n", value);

	proc->reg[proc->op->ar[2]] = value;











	//
	//
	// addr = proc->op->ar[0];
	// reg_nb = proc->op->ar[2] - 1;
	// if (proc->op->ar_typ[0] == REG_CODE)
	// 	addr = proc->reg[proc->op->ar[0] - 1];
	// if (proc->op->ar_typ[1] == REG_CODE)
	// 	addr += proc->reg[proc->op->ar[1] - 1];
	// else
	// 	addr += proc->op->ar[1];
	// proc->reg[reg_nb] = 0;
	// proc->reg[reg_nb] |= vm->mem[addr];
	// proc->reg[reg_nb] <<= 8;
	// proc->reg[reg_nb] |= vm->mem[addr + 1];
	// proc->reg[reg_nb] <<= 8;
	// proc->reg[reg_nb] |= vm->mem[addr + 2];
	// proc->reg[reg_nb] <<= 8;
	// proc->reg[reg_nb] |= vm->mem[addr + 3];
	// proc->carry = (proc->reg[reg_nb] == 0) ? 1 : 0;
	/*proc->carry = 0;
	if (proc->reg[reg_nb] == 0)
		proc->carry = 1;*/
}
