/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:43:34 by lchety            #+#    #+#             */
/*   Updated: 2017/12/04 17:13:26 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	name_color(int i)
{
	attron(A_BOLD);
	if (i == 1)
		attron(COLOR_PAIR(NC_P_GREEN_BLING));
	else if (i == 2)
		attron(COLOR_PAIR(NC_P_BLUE_BLING));
	else if (i == 3)
		attron(COLOR_PAIR(NC_P_RED_BLING));
	else if (i == 4)
		attron(COLOR_PAIR(NC_P_CYAN_BLING));
}

int		display_players(t_vm *vm)
{
	int i;
	int b;

	b = 11;
	i = 1;
	while (i < vm->nb_player + 1)
	{
		attron(COLOR_PAIR(NC_P_WHITE));
		mvprintw(b, 3 * (MEM_SIZE / 64) + 7, "Player -%d : ", i);
		name_color(i);
		mvprintw(b, 3 * (MEM_SIZE / 64) + 9 + 10, "%s", vm->player[i].name);
		attron(COLOR_PAIR(NC_P_WHITE));
		mvprintw(b + 1, 3 * (MEM_SIZE / 64) + 7 + 1, "Last live : ");
		if (!vm->player[i].last_live)
			mvprintw(b + 1, 3 * (MEM_SIZE / 64) + 7 + 1 + 25, "0");
		else
			mvprintw(b + 1, 3 * (MEM_SIZE / 64) + 7 + 1 + 25, "%d   ",
			vm->player[i].last_live + 1);
		mvprintw(b + 2, 3 * (MEM_SIZE / 64) + 7 + 1,
		"Live in current period : %d      ",
		vm->player[i].life_signal);
		b += 4;
		i++;
	}
	return (b);
}

void	display_menu(t_vm *vm)
{
	int line;

	attron(COLOR_PAIR(NC_P_WHITE));
	if (vm->pause == 1)
		mvprintw(3, 3 * (MEM_SIZE / 64) + 7, "** PAUSED **");
	if (vm->pause != 1)
		mvprintw(3, 3 * (MEM_SIZE / 64) + 7, "** RUNNING **");
	mvprintw(5, 3 * (MEM_SIZE / 64) + 7, "Speed : %d  ",
	100 - (vm->delay / 10000));
	mvprintw(8, 3 * (MEM_SIZE / 64) + 7, "Cycles : %d    ", vm->cycle);
	mvprintw(10, 3 * (MEM_SIZE / 64) + 7, "Processes : %d     ",
	count_proc(vm));
	line = display_players(vm);
	line = display_breakdown(vm, line);
	mvprintw(line + 2, 3 * (MEM_SIZE / 64) + 7, "CYCLE_TO_DIE : %d     ",
	vm->ctd);
	mvprintw(line + 4, 3 * (MEM_SIZE / 64) + 7, "CYCLE_DELTA : %d    ",
	CYCLE_DELTA);
	mvprintw(line + 6, 3 * (MEM_SIZE / 64) + 7, "NBR_LIVE : %d    ",
	NBR_LIVE);
	mvprintw(line + 8, 3 * (MEM_SIZE / 64) + 7, "MAX_CHECKS : %d    ",
	MAX_CHECKS);
	attron(COLOR_PAIR(NC_P_BLACK_B));
}
