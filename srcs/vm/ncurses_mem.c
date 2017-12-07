/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:25:41 by lchety            #+#    #+#             */
/*   Updated: 2017/12/04 22:16:52 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		display_pc(t_vm *vm, int i)
{
	if (vm->ram[i].num == -1)
		attron(COLOR_PAIR(NC_P_GREEN_PC));
	else if (vm->ram[i].num == -2)
		attron(COLOR_PAIR(NC_P_BLUE_PC));
	else if (vm->ram[i].num == -3)
		attron(COLOR_PAIR(NC_P_RED_PC));
	else if (vm->ram[i].num == -4)
		attron(COLOR_PAIR(NC_P_CYAN_PC));
	vm->ram[i].pc = 0;
}

static void		life(t_vm *vm, int i)
{
	attron(A_BOLD);
	if (vm->ram[i].num == -1)
		attron(COLOR_PAIR(NC_P_GREEN_LIFE));
	else if (vm->ram[i].num == -2)
		attron(COLOR_PAIR(NC_P_BLUE_LIFE));
	else if (vm->ram[i].num == -3)
		attron(COLOR_PAIR(NC_P_RED_LIFE));
	else if (vm->ram[i].num == -4)
		attron(COLOR_PAIR(NC_P_CYAN_LIFE));
	vm->ram[i].live--;
}

static void		bling(t_vm *vm, int i)
{
	attron(A_BOLD);
	if (vm->ram[i].num == -1)
		attron(COLOR_PAIR(NC_P_GREEN_BLING));
	else if (vm->ram[i].num == -2)
		attron(COLOR_PAIR(NC_P_BLUE_BLING));
	else if (vm->ram[i].num == -3)
		attron(COLOR_PAIR(NC_P_RED_BLING));
	else if (vm->ram[i].num == -4)
		attron(COLOR_PAIR(NC_P_CYAN_BLING));
	vm->ram[i].blingbling--;
}

static void		mem_main(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		attron(COLOR_PAIR(NC_P_GREY));
		if (vm->ram[i].num == -1)
			attron(COLOR_PAIR(NC_P_GREEN));
		else if (vm->ram[i].num == -2)
			attron(COLOR_PAIR(NC_P_BLUE));
		else if (vm->ram[i].num == -3)
			attron(COLOR_PAIR(NC_P_RED));
		else if (vm->ram[i].num == -4)
			attron(COLOR_PAIR(NC_P_CYAN));
		if (vm->ram[i].blingbling)
			bling(vm, i);
		if (vm->ram[i].pc)
			display_pc(vm, i);
		if (vm->ram[i].live)
			life(vm, i);
		mvprintw((3 + i / 64), (4 + (i % 64) * 3), "%02x",
		(unsigned char)vm->ram[i].mem);
		attroff(A_BOLD);
		i++;
	}
}

void			display_mem(t_vm *vm)
{
	mem_main(vm);
}
