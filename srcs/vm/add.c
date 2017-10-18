/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:57:54 by lchety            #+#    #+#             */
/*   Updated: 2017/10/17 13:08:37 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add(t_vm *vm, t_proc *proc)
{
	// printf(">>>>ENTER_ADD<<<<\n");
	int		sum;

	sum = proc->reg[proc->op->ar[0]] + proc->reg[proc->op->ar[1]];
	proc->reg[proc->op->ar[2]] = sum;
	proc->carry = (sum == 0) ? 1 : 0;
}
