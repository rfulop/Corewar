/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:38:24 by lchety            #+#    #+#             */
/*   Updated: 2017/12/04 17:44:14 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			modulo(int a, int b)
{
	if (a % b >= 0)
		return (a % b);
	else
		return ((a % b) + b);
}

int			is_opcode(char data)
{
	if (data > 0 && data < 17)
		return (1);
	return (0);
}

int			count_octet(int octet, t_optab *ref)
{
	if (octet == 1)
		return (REG_SIZE);
	else if (octet == 2)
		return ((ref->direct_size) ? 2 : 4);
	else if (octet == 3)
		return (IND_SIZE);
	return (0);
}

void		dump(t_vm *vm)
{
	if (vm->cycle == vm->dump)
	{
		show_mem(vm);
		exit(1);
	}
}
