/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:13:38 by lchety            #+#    #+#             */
/*   Updated: 2017/12/07 16:28:53 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		show_mem(t_vm *vm)
{
	int		i;

	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if (!(i % 64) && i)
			ft_printf("%#.4x : ", i);
		ft_printf("%02x ", (unsigned char)vm->ram[i].mem);
		if (i / 64 != (i + 1) / 64)
			ft_printf("\n");
		i++;
	}
	ft_printf("\n\n");
}

void		debug_display_proc(t_vm *vm)
{
	t_proc	*tmp;
	int		i;

	i = 0;
	tmp = vm->proc;
	while (tmp)
	{
		move(24 + i, 198);
		printw("Proc n:%d on:%d num:%d pc:%d live:%d", i, tmp->active,
				tmp->num, tmp->pc, tmp->last_live);
		tmp = tmp->next;
		i++;
	}
}

static void	display_args(t_proc *proc, int n)
{
	if (proc->op.ar_typ[n] == REG_CODE)
		ft_printf("r");
	ft_printf("%d", proc->op.ar[n]);
}

void		show_operations(t_proc *proc)
{
	int		nb_arg;
	int		i;

	i = 0;
	nb_arg = g_op_tab[proc->op.code - 1].nb_arg;
	ft_printf("P%5d | %s", proc->id + 1, g_op_tab[proc->op.code - 1].inst);
	while (i < nb_arg)
	{
		ft_printf(" ");
		display_args(proc, i);
		i++;
	}
}

void		show_pc_move(t_vm *vm, t_proc *proc)
{
	int		i;
	int		move_size;

	i = 0;
	move_size = proc->pc - proc->last_pc;
	if (move_size > 1)
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x)", move_size,
			proc->last_pc, proc->pc);
		while (i < move_size)
		{
			ft_printf(" %02x", (unsigned char)vm->ram[(proc->last_pc + i)
				% MEM_SIZE].mem);
			i++;
		}
		ft_printf(" \n");
	}
}
