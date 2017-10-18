/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlambert <mlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 14:09:08 by mlambert          #+#    #+#             */
/*   Updated: 2017/10/14 20:49:36 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	or(t_vm *vm, t_proc *proc)
{
	unsigned int	ar1;
	unsigned int	ar2;

	if (proc->op->ar_typ[0] == T_REG)
		ar1 = proc->reg[proc->op->ar[0]];
	else
		ar1 = proc->op->ar[0];
	if (proc->op->ar_typ[1] == T_REG)
		ar2 = proc->reg[proc->op->ar[1]];
	else
		ar2 = proc->op->ar[1];
 	proc->reg[proc->op->ar[2]] = ar1 | ar2;
 	proc->carry = ((ar1 | ar2) == 0) ? 1 : 0;
}
