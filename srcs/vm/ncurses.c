/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchety <lchety@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 12:07:36 by lchety            #+#    #+#             */
/*   Updated: 2017/10/07 19:55:40 by lchety           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_ncurses(WINDOW **w)
{
	*w = initscr();
	start_color();			/* Start color 			*/
	cbreak(); //getch() no block
	nodelay(*w, TRUE);
}

void	call_ncurses(t_vm *vm)
{
	int i;
	int ret;

	i = 0;
	ret = 0;

	init_color(35, 350, 350, 350);//basic grey
	init_pair(15, 35, COLOR_BLACK);//basic

	init_pair(20, COLOR_GREEN, COLOR_BLACK);//player_1

	init_color(36, 150, 1000, 150);//fluo_green
	init_color(38, 500, 1000, 500);//blingbling_green
	init_pair(21, COLOR_GREEN, 36);//player_1_highlight
	init_pair(24, 38, COLOR_BLACK);//player_1_blingbling

	init_pair(22, COLOR_BLUE, COLOR_BLACK);//player_2
	init_color(COLOR_BLUE, 200, 200, 800);//blue change

	init_color(37, 400, 400, 1000);//fluo_blue
	init_pair(23, COLOR_BLUE, 37);//player_2_highlight
	init_pair(25, 37, COLOR_BLACK);//player_2_blingbling

	init_pair(26, COLOR_GREEN, COLOR_RED);//life highlight

	move(0,0);
	while (i < MEM_SIZE)
	{
		// printf("FOOOOOO\n");
		attron(COLOR_PAIR(15));
		move(i / 64, (i % 64) * 3);
		if ((is_pc(vm, i)))
		{
			if (vm->ram[i].num == -1)
				attron(COLOR_PAIR(21));
			else if (vm->ram[i].num == -2)
				attron(COLOR_PAIR(23));
			attron(A_STANDOUT);
		}
		else if (vm->ram[i].num == -1)
		{
			attron(COLOR_PAIR(20));
		}
		else if (vm->ram[i].num == -2)
		{
			attron(COLOR_PAIR(22));
		}

		if (vm->ram[i].blingbling)
		{
			attron(A_BOLD);
			if (vm->ram[i].num == -1)
				attron(COLOR_PAIR(24));
			if (vm->ram[i].num == -2)
				attron(COLOR_PAIR(25));
			vm->ram[i].blingbling--;
		}

		if (vm->ram[i].live)
		{
			attron(COLOR_PAIR(26));
			vm->ram[i].live--;
		}

		printw("%02x", (unsigned char)vm->ram[i].mem);
		attroff(A_STANDOUT);
		attroff(A_BOLD);
		attroff(COLOR_PAIR(35));
		i++;
	}
	move(5, 200);
	printw("Delay : %d", vm->delay);
	move(10, 200);
	printw("Cycles : %d", vm->cycle);
	move(12, 200);
	printw("Keycode : %d", vm->keycode);
	move(14, 200);
	printw("Proc Nb : %d", count_proc(vm));
	move(20, 200);
	printw("Cycle to die : %d", vm->ctd);
	move(22, 200);
	printw("Live P1 : %08d", vm->player[1].life_signal);
	move(26, 210);

	// debug_display_proc(vm);

	refresh();

}
