/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_breakdown.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 16:06:02 by rfulop            #+#    #+#             */
/*   Updated: 2017/12/05 09:23:31 by amacieje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		loop_breakdown(int line, int col, int until)
{
	int i;

	i = 0;
	while (i < until && i + col <= BREAK_DIS)
	{
		mvprintw(line, 3 * (MEM_SIZE / 64) + 7 + i + col, "-");
		++i;
	}
	return (i);
}

int		last_breakdown(t_vm *vm, int line, int p)
{
	int i;
	int col;

	col = 1;
	while (p <= MAX_PLAYERS)
	{
		name_color(p);
		i = 0;
		while (i < vm->player[p].last_period)
		{
			mvprintw(line, 3 * (MEM_SIZE / 64) + 7 + i + col, "-");
			++i;
		}
		col += i;
		++p;
	}
	attron(COLOR_PAIR(NC_P_WHITE));
	while (col <= BREAK_DIS)
	{
		mvprintw(line, 3 * (MEM_SIZE / 64) + 7 + col, "-");
		++col;
	}
	mvprintw(line, 3 * (MEM_SIZE / 64) + 7 + col, "]");
	return (line);
}

int		current_breakdown(t_vm *vm, int line, int tot_live)
{
	int		p;
	int		i;
	int		col;
	float	p_lives;

	p = 1;
	col = 1;
	while (p <= MAX_PLAYERS)
	{
		p_lives = get_p_lives(vm, p, tot_live);
		name_color(p);
		i = loop_breakdown(line, col, p_lives);
		vm->player[p].tot = i;
		col += i;
		++p;
	}
	return (col);
}

int		display_breakdown(t_vm *vm, int line)
{
	int col;
	int dv;
	int tot_live;

	mvprintw(line, 3 * (MEM_SIZE / 64) + 7,
	"Live breakdown for current period :");
	mvprintw(line + 1, 3 * (MEM_SIZE / 64) + 7, "[");
	tot_live = get_nb_live(vm);
	dv = get_dv(tot_live);
	col = current_breakdown(vm, line + 1, tot_live);
	attron(COLOR_PAIR(NC_P_WHITE));
	while (col <= BREAK_DIS)
	{
		mvprintw(line + 1, 3 * (MEM_SIZE / 64) + 7 + col, "-");
		++col;
	}
	mvprintw(line + 1, 3 * (MEM_SIZE / 64) + 7 + col, "]");
	mvprintw(line + 3, 3 * (MEM_SIZE / 64) + 7,
	"Live breakdown for last period :");
	mvprintw(line + 4, 3 * (MEM_SIZE / 64) + 7, "[");
	line = last_breakdown(vm, line + 4, 1);
	return (line);
}
