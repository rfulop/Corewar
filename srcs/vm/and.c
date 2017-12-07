/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 12:13:33 by lchety            #+#    #+#             */
/*   Updated: 2017/12/01 14:22:10 by amacieje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				and(t_vm *vm, t_proc *proc)
{
	unsigned int	ar1;
	unsigned int	ar2;

	if (!check_params(&proc->op))
		return ;
	if (proc->op.ar_typ[0] == T_REG)
		ar1 = proc->reg[proc->op.ar[0]];
	else
		ar1 = proc->op.ar[0];
	if (proc->op.ar_typ[1] == T_REG)
		ar2 = proc->reg[proc->op.ar[1]];
	else
		ar2 = proc->op.ar[1];
	proc->reg[proc->op.ar[2]] = ar1 & ar2;
	proc->carry = ((ar1 & ar2) == 0) ? 1 : 0;
	if (0x4 & vm->verbosity)
	{
		show_operations(proc);
		ft_printf("\n");
	}
}
