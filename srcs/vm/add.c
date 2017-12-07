/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:57:54 by lchety            #+#    #+#             */
/*   Updated: 2017/12/01 14:21:10 by amacieje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		add(t_vm *vm, t_proc *proc)
{
	int		sum;

	if (!check_params(&proc->op))
		return ;
	sum = proc->reg[proc->op.ar[0]] + proc->reg[proc->op.ar[1]];
	proc->reg[proc->op.ar[2]] = sum;
	proc->carry = (sum == 0) ? 1 : 0;
	if (0x4 & vm->verbosity)
	{
		show_operations(proc);
		ft_printf("\n");
	}
}
