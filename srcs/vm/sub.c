/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlambert <mlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:08:30 by mlambert          #+#    #+#             */
/*   Updated: 2017/12/04 15:47:26 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	sub(t_vm *vm, t_proc *proc)
{
	int	n;

	if (!check_params(&proc->op))
		return ;
	n = proc->reg[proc->op.ar[0]] - proc->reg[proc->op.ar[1]];
	proc->reg[proc->op.ar[2]] = n;
	proc->carry = (n == 0) ? 1 : 0;
	if (0x4 & vm->verbosity)
	{
		show_operations(proc);
		ft_printf("\n");
	}
}
