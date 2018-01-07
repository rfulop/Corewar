/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:07:36 by lchety            #+#    #+#             */
/*   Updated: 2017/12/04 22:26:53 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_color_pair(void)
{
	init_pair(NC_P_GREY, NC_C_GREY, NC_C_BLACK);
	init_pair(NC_P_WHITE, NC_C_WHITE, NC_C_BLACK);
	init_pair(NC_P_GREEN, NC_C_GREEN, NC_C_BLACK);
	init_pair(NC_P_BLUE, NC_C_BLUE, NC_C_BLACK);
	init_pair(NC_P_RED, NC_C_RED, NC_C_BLACK);
	init_pair(NC_P_CYAN, NC_C_CYAN, NC_C_BLACK);
	init_pair(NC_P_GREEN_BLING, NC_C_GREEN_BLING, NC_C_BLACK);
	init_pair(NC_P_BLUE_BLING, NC_C_BLUE_BLING, NC_C_BLACK);
	init_pair(NC_P_RED_BLING, NC_C_RED_BLING, NC_C_BLACK);
	init_pair(NC_P_CYAN_BLING, NC_C_CYAN_BLING, NC_C_BLACK);
	init_pair(NC_P_GREEN_PC, NC_C_BLACK, NC_C_GREEN);
	init_pair(NC_P_BLUE_PC, NC_C_BLACK, NC_C_BLUE);
	init_pair(NC_P_RED_PC, NC_C_BLACK, NC_C_RED);
	init_pair(NC_P_CYAN_PC, NC_C_BLACK, NC_C_CYAN);
	init_pair(NC_P_GREEN_LIFE, NC_C_WHITE, NC_C_GREEN);
	init_pair(NC_P_BLUE_LIFE, NC_C_WHITE, NC_C_BLUE);
	init_pair(NC_P_RED_LIFE, NC_C_WHITE, NC_C_RED);
	init_pair(NC_P_CYAN_LIFE, NC_C_WHITE, NC_C_CYAN);
	init_pair(NC_P_BLACK_B, NC_C_BLACK, NC_C_BLACK);
	init_pair(NC_P_WHITE_B, NC_C_WHITE, NC_C_WHITE);
}

void	colors_init(void)
{
	init_color(NC_C_WHITE, 800, 800, 800);
	init_color(NC_C_BLACK, 0, 0, 0);
	init_color(NC_C_GREY, 350, 350, 350);
	init_color(NC_C_GREEN, 410, 750, 300);
	init_color(NC_C_BLUE, 200, 300, 600);
	init_color(NC_C_RED, 700, 150, 200);
	init_color(NC_C_CYAN, 100, 500, 600);
	init_color(NC_C_GREEN_BLING, 600, 1000, 500);
	init_color(NC_C_BLUE_BLING, 400, 600, 1000);
	init_color(NC_C_RED_BLING, 1000, 300, 400);
	init_color(NC_C_CYAN_BLING, 300, 1000, 1000);
	init_color_pair();
}

void	border_ncurses(void)
{
	int i;
	int j;

	i = 0;
	j = 0;
	display_linux();
	attron(COLOR_PAIR(NC_P_WHITE_B));
	while (++i < MEM_SIZE / 64 + 5)
	{
		j = -1;
		while (++j < 3 * (MEM_SIZE / 64) + 72)
		{
			if (i == 1 || j == 0 || i == MEM_SIZE / 64 + 4
					|| j == 3 * (MEM_SIZE / 64) + 5 ||
					j == 3 * (MEM_SIZE / 64) + 70
					|| j == 3 * (MEM_SIZE / 64) + 71 || j == 1)
				mvprintw(i, j, " ");
		}
	}
}

void	call_ncurses(t_vm *vm)
{
	int i;
	int ret;

	i = -1;
	ret = 0;
	if (!vm->ncurses)
		return ;
	if (vm->boost && !vm->winner && (vm->cycle % BOOST_CYCLES))
		return ;
	display_mem(vm);
	display_menu(vm);
	controller(vm);
	usleep(vm->delay);
	refresh();
}

void	init_ncurses(WINDOW **w)
{
	*w = initscr();
	if (has_colors() == FALSE)
	{
		ft_printf("Your terminal does not support colors.\n");
		endwin();
		exit(1);
	}
	start_color();
	colors_init();
	border_ncurses();
	cbreak();
	nodelay(*w, TRUE);
	curs_set(0);
}
